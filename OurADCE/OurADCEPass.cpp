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
    std::vector<BasicBlock *> unreachableInstrucions;
    for(BasicBlock &BB : F){
      if(!reachableInstructions[&BB]){
        unreachableInstrucions.push_back(&BB);
      }
    }

    for(BasicBlock *ui : unreachableInstrucions){
        ui->eraseFromParent();
    }
  }

  bool runOnFunction(Function &F) override{
    for(BasicBlock &BB : F){
      reachableInstructions[&BB] = false;
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


char OurADCE::ID = 0;
static RegisterPass<OurADCE> X("our-adce", "OurADCE pass", false, false);
