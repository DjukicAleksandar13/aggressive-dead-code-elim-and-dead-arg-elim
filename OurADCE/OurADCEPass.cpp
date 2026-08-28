#include "llvm/Pass.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"
#include "OurCFG.h"

using namespace llvm;

namespace {
struct OurADCE : public FunctionPass {
  std::unordered_map<BasicBlock *, bool> reachableInstructions;
  std::vector<BasicBlock *> BBList;
  bool livenessChange;

  static char ID;
  OurADCE() : FunctionPass(ID) {}

  void findReachableInstructions(Function &F){
    OurCFG *CFG = new OurCFG(F);
    CFG->DFS(&F.front());

    for(BasicBlock &BB : F){
      if(CFG->isReachable(&BB) && reachableInstructions[&BB] == false){
        reachableInstructions[&BB] = true;
        livenessChange = true;
      }
    }
  }

  void eliminateUnreachableInstructions(Function &F){
    for(BasicBlock *BB : BBList){
      if(!reachableInstructions[BB]){
        BB->eraseFromParent();
      }
    }
  }

  bool runOnFunction(Function &F) override{
    for(BasicBlock &BB : F){
      reachableInstructions[&BB] = false;
      BBList.push_back(&BB);
    }

    do{
      livenessChange = false;
      findReachableInstructions(F);
    }while(livenessChange);

    eliminateUnreachableInstructions(F);

    return true;
  }
};
}

char OurADCE::ID = 0;
static RegisterPass<OurADCE> X("our-adce", "OurADCE pass", false, false);
