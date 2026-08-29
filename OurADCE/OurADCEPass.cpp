#include "llvm/Pass.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/Analysis/ValueTracking.h"
#include "OurCFG.h"

using namespace llvm;

namespace {
	struct OurADCE : public FunctionPass {
		std::unordered_map<BasicBlock *, bool> reachableInstructions;
		std::vector<Instruction *> CurrentInstructions;
		std::vector<Instruction *> InstructionsToRemove;
		std::unordered_set<Instruction *> LiveInstructions;
        std::unordered_set<Value *> LiveValues;
        bool livenessChange;

		static char ID;
		OurADCE() : FunctionPass(ID) {}

		void findReachableInstructions(Function &F) {
			OurCFG *CFG = new OurCFG(F);
			CFG->DFS(&F.front());

    		for (BasicBlock &BB : F) {
      			if (CFG->isReachable(&BB)) {
					reachableInstructions[&BB] = true;
      			}
    		}
  		}

		void eliminateUnreachableInstructions(Function &F) {
          findReachableInstructions(F);
		  std::vector<BasicBlock *> unreachableInstrucions;
		  for (BasicBlock &BB : F) {
		    if (!reachableInstructions[&BB]) {
		      unreachableInstrucions.push_back(&BB);
		    }
		  }

          if (unreachableInstrucions.size() > 0) { livenessChange = true; }

		  for (BasicBlock *ui : unreachableInstrucions) {
		    ui->eraseFromParent();
		  }
		}

        void addToLive(Instruction *I) {
          if (LiveInstructions.insert(I).second) {
            CurrentInstructions.push_back(I);
          }
        }

        bool potentialLive(Instruction *I) {
          if (isa<ReturnInst>(I) || isa<ResumeInst>(I) || isa<CallBase>(I) || I->isTerminator()) return true;

          if (auto *LoadInstr = dyn_cast<LoadInst>(I)) {
            return LoadInstr->isVolatile();
          }

          if (auto *StoreInstr = dyn_cast<StoreInst>(I)) {
            return StoreInstr->isVolatile();
          }

          return false;
        }

		void eliminateDeadInstructions(Function &F) {
			LiveInstructions.clear();
			CurrentInstructions.clear();
			InstructionsToRemove.clear();
            LiveValues.clear();

			for (BasicBlock &BB : F) {
				for (Instruction &I : BB) {
					if (potentialLive(&I)) {
						addToLive(&I);
					}
				}
			}

            bool ind;

            do {
              ind = false;

			  while (!CurrentInstructions.empty()) {
				  Instruction *currInst = CurrentInstructions.back();
				  CurrentInstructions.pop_back();
				  size_t valueCount = LiveValues.size();
                  size_t instructionCount = LiveInstructions.size();

                  for (Value *Val: currInst->operands()) {
                    if (Instruction *Operand = dyn_cast<Instruction>(Val)) {
                      addToLive(Operand);
                    }
                  }

                  if (auto *LoadInstr = dyn_cast<LoadInst>(currInst)) {
                    Value *Ptr = getUnderlyingObject(LoadInstr->getPointerOperand());
                    if (Ptr != nullptr) { LiveValues.insert(Ptr); }
                  }

                  if (LiveValues.size() != valueCount || LiveInstructions.size() != instructionCount) {
                    ind = true;
                  }
			  }

              size_t instCount = LiveInstructions.size();

              for (BasicBlock &BB : F) {
                for (Instruction &I : BB) {
                  auto *StoreInstr = dyn_cast<StoreInst>(&I);
                  if (!StoreInstr) continue;
                  Value *Ptr = getUnderlyingObject(StoreInstr->getPointerOperand());
                  if (Ptr == nullptr) { continue; }

                  if (LiveValues.count(Ptr)) {
                    addToLive(StoreInstr);
                  }
                }
              }

              if (LiveInstructions.size() != instCount) { ind = true; }

            } while (ind);

			for (BasicBlock &BB : F) {
				for (Instruction &I : BB) {
                    if (I.isTerminator()) { continue; }
					if (LiveInstructions.count(&I) != 0) { continue; }
					InstructionsToRemove.push_back(&I);
				}
			}

			if (InstructionsToRemove.size() > 0) { livenessChange = true; }

			for (Instruction *Instr : InstructionsToRemove) {
      			Instr->eraseFromParent();
    		}
		}

		bool runOnFunction(Function &F) override {
			for (BasicBlock &BB : F) {
  				reachableInstructions[&BB] = false;
			}

            do {
              livenessChange = false;
			  eliminateDeadInstructions(F);
  			  eliminateUnreachableInstructions(F);
            } while (livenessChange);

		    return true;
		}
	};
}

char OurADCE::ID = 0;
static RegisterPass<OurADCE> X("our-adce", "OurADCE pass", false, false);