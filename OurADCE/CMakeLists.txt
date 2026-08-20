add_llvm_library( LLVMOurADCE MODULE BUILDTREE_ONLY
  OurADCEPass.cpp
  OurCFG.cpp

  DEPENDS
  intrinsics_gen
  PLUGIN_TOOL
  opt
  )
