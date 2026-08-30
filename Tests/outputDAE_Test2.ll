; ModuleID = 'DAE_Test2.ll'
source_filename = "DAE_Test2.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

module asm ".globl _ZSt21ios_base_library_initv"

; Function Attrs: mustprogress noinline norecurse nounwind optnone uwtable
define dso_local noundef i32 @main() #0 {
  %1 = alloca double, align 8
  %2 = alloca double, align 8
  store double 2.100000e+00, ptr %1, align 8
  store double 3.300000e+00, ptr %2, align 8
  %3 = load double, ptr %1, align 8
  %4 = load double, ptr %2, align 8
  %5 = call i1 @_Z7odaberiiiiddb.1(i32 13, i32 2003, i1 true)
  %6 = load double, ptr %2, align 8
  %7 = load double, ptr %1, align 8
  %8 = call i1 @_Z7odaberiiiiddb.1(i32 99, i32 101, i1 false)
  %9 = load double, ptr %2, align 8
  %10 = call i1 @_Z7odaberiiiiddb.1(i32 1000, i32 1000, i1 true)
  ret i32 0
}

define i1 @_Z7odaberiiiiddb.1(i32 %0, i32 %1, i1 %2) {
  %4 = alloca i1, align 1
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca double, align 8
  %9 = alloca double, align 8
  %10 = alloca i8, align 1
  store i32 %0, ptr %5, align 4
  store i32 %1, ptr %7, align 4
  %11 = zext i1 %2 to i8
  store i8 %11, ptr %10, align 1
  %12 = load i32, ptr %5, align 4
  %13 = load i32, ptr %7, align 4
  %14 = icmp sgt i32 %12, %13
  br i1 %14, label %15, label %16

15:                                               ; preds = %3
  store i1 true, ptr %4, align 1
  br label %19

16:                                               ; preds = %3
  %17 = load i8, ptr %10, align 1
  %18 = trunc i8 %17 to i1
  store i1 %18, ptr %4, align 1
  br label %19

19:                                               ; preds = %16, %15
  %20 = load i1, ptr %4, align 1
  ret i1 %20
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
