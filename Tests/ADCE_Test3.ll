; ModuleID = 'ADCE_Test3.cpp'
source_filename = "ADCE_Test3.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

module asm ".globl _ZSt21ios_base_library_initv"

; Function Attrs: mustprogress noinline norecurse nounwind optnone uwtable
define dso_local noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca double, align 8
  store i32 0, ptr %1, align 4
  store float 2.000000e+00, ptr %2, align 4
  store float 3.000000e+00, ptr %2, align 4
  store float 0x4019333340000000, ptr %2, align 4
  store float 0x401ACCCCC0000000, ptr %3, align 4
  store double 0x400912B4D8BA40D9, ptr %4, align 8
  %5 = load double, ptr %4, align 8
  %6 = fcmp olt double %5, 2.900000e+00
  br i1 %6, label %7, label %8

7:                                                ; preds = %0
  store double 0x4058BEFD4BF0995B, ptr %4, align 8
  br label %8

8:                                                ; preds = %7, %0
  ret i32 0
}

attributes #0 = { mustprogress noinline norecurse nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 17.0.0"}
