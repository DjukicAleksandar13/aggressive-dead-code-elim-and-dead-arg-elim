#include "llvm/Pass.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"
#include "OurCFG.h"

using namespace llvm;

namespace {
	struct OurADCE : public FunctionPass {
		std::unordered_map<BasicBlock *, bool> reachableInstructions;
		std::vector<Instruction *> CurrentInstructions;
		std::vector<Instruction *> InstructionsToRemove;
		std::unordered_set<Instruction *> LiveInstructions;
		bool livenessChange;

		static char ID;
		OurADCE() : FunctionPass(ID) {}

		void findReachableInstructions(Function &F) {
			OurCFG *CFG = new OurCFG(F);
			CFG->DFS(&F.front());

    		for (BasicBlock &BB : F) {
      			if (CFG->isReachable(&BB) && reachableInstructions[&BB] == false) {
					reachableInstructions[&BB] = true;
					livenessChange = true;
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

		  for (BasicBlock *ui : unreachableInstrucions) {
		    ui->eraseFromParent();
		  }
		}

		void eliminateDeadInstructions(Function &F) {
			LiveInstructions.clear();
			CurrentInstructions.clear();
			InstructionsToRemove.clear();

			for (BasicBlock &BB : F) {
				for (Instruction &I : BB) {
					if (I.isTerminator() || I.mayHaveSideEffects()) {
						addToLive(&I);
					}
				}
			}

			while (!CurrentInstructions.empty()) {
				Instruction *currInst = CurrentInstructions.back();
				CurrentInstructions.pop_back();
				for (Value *V : currInst->operands()) {
					if (Instruction *I = dyn_cast<Instruction>(V)) {
						addToLive(I);
					}
				}
			}

			for (BasicBlock &BB : F) {
				for (Instruction &I : BB) {
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