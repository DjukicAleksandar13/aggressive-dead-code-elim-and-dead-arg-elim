#include "OurCFG.h"

OurCFG::OurCFG(llvm::Function &F) {
  FunctionName = F.getName().str();
  CreateCFG(F);
}

void OurCFG::CreateCFG(Function &F) {
  for(BasicBlock &BB : F) {
    AdjacencyList[&BB] = {};
    for (BasicBlock *Successor : successors(&BB)) {
        AdjacencyList[&BB].push_back(Successor);
    }
  }
}

void OurCFG::DFS(llvm::BasicBlock *Current) {
  Visited.insert(Current);

  for(BasicBlock *Successor : AdjacencyList[Current]) {
    if (Visited.find(Successor) == Visited.end()) {
      DFS(Successor);
    }
  }
}

bool OurCFG::isReachable(llvm::BasicBlock *BB) {
  return Visited.find(BB) != Visited.end();
}
