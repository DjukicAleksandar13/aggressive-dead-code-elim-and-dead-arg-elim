#include "llvm/Pass.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Analysis/ValueTracking.h"

using namespace llvm;

namespace {
    struct OurDAE : public ModulePass {
        std::unordered_map<unsigned, bool> DeadArgs;

        static char ID;
	OurDAE() : ModulePass(ID) {}

        bool checkDeadArg(Argument &A) {
	    for (User *U : A.users()) {
                StoreInst *StoreInstr = dyn_cast<StoreInst>(U);
                if (!StoreInstr) { return false; }
	            Value *val = getUnderlyingObject(StoreInstr->getPointerOperand());
	            if (isa<GlobalVariable>(val)) { return false; }
                AllocaInst *Alloca = dyn_cast<AllocaInst>(StoreInstr->getPointerOperand());
                if (!Alloca) { return false; }

                for (User *AllocaUser : Alloca->users()) {
                    if (isa<LoadInst>(AllocaUser))
                        return false;

                    if (!isa<StoreInst>(AllocaUser))
                        return false;
                }
            }

            return true;
        }

        bool anyDead(Function *F) {
            bool argDead = false;
            unsigned argNum = 0;
	    for (Argument &A : F->args()) {
	        if (checkDeadArg(A)) {
	            DeadArgs[argNum] = true;
	            argDead = true;
	        } else {
                    DeadArgs[argNum] = false;
                }
                argNum++;
	    }
            return argDead;
        }

        void eliminateDeadArguments(Module &M) {
            std::vector<Function *> funcVector;
            for (Function &F : M) {
                funcVector.push_back(&F);
            }

            for (Function *F : funcVector) {
                if (!F->isDeclaration()) {
                    DeadArgs.clear();

                    if (!anyDead(F)) { continue; }

                    std::vector<Type *> newParams;
                    unsigned paramNum = 0;
                    for (Argument &A : F->args()) {
                        if (!DeadArgs[paramNum]) {
                            newParams.push_back(A.getType());
                        }
                        paramNum++;
                    }

                    FunctionType *newType = FunctionType::get(F->getReturnType(), newParams, false);
                    Function *newFunc = Function::Create(newType, F->getLinkage(), F->getName(), &M);

                    auto newArgs = newFunc->arg_begin();
                    paramNum = 0;
                    for (Argument &A : F->args()) {
                        if (!DeadArgs[paramNum]) {
                            newArgs->setName(A.getName());
                            A.replaceAllUsesWith(&*newArgs);
                            newArgs++;
                        }
                        paramNum++;
                    }

                    std::vector<User *> users(F->user_begin(), F->user_end());
                    for (User *U : users) {
                        if (CallInst *CallInstr = dyn_cast<CallInst>(U)) {
                            IRBuilder<> Builder(CallInstr);
                            std::vector<Value *> funcArgs;
                            unsigned argSize = CallInstr->arg_size();

                            for (unsigned i = 0; i < argSize; i++) {
                                if (!DeadArgs[i]) {
                                    funcArgs.push_back(CallInstr->getArgOperand(i));
                                }
                            }

                            CallInst *newCallInstr = Builder.CreateCall(newFunc, funcArgs);
                            newCallInstr->setCallingConv(CallInstr->getCallingConv());
                            CallInstr->replaceAllUsesWith(newCallInstr);
                            CallInstr->eraseFromParent();
                        }
                    }

                    for (Argument &A : F->args()) {
                        if (DeadArgs[A.getArgNo()]) {
                            std::vector<User *> users(A.user_begin(), A.user_end());
                            for (User *U : users) {
                                if (StoreInst *StoreInstr = dyn_cast<StoreInst>(U)) {
                                    StoreInstr->eraseFromParent();
                                }
                            }
                        }
                    }

                    newFunc->splice(newFunc->end(), F);
                    F->replaceAllUsesWith(newFunc);
                    F->eraseFromParent();
                }
            }
        }

	bool runOnModule(Module &M) override {
            eliminateDeadArguments(M);

	    return true;
	}
    };
}

char OurDAE::ID = 0;
static RegisterPass<OurDAE> X("our-dae", "OurDAE pass", false, false);