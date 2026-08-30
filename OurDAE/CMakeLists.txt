add_llvm_library( LLVMOurDAE MODULE BUILDTREE_ONLY
    OurDAEPass.cpp

    DEPENDS
    intrinsics_gen
    PLUGIN_TOOL
    opt
)
