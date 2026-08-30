; ModuleID = 'DAE_Test2.cpp'
source_filename = "DAE_Test2.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

module asm ".globl _ZSt21ios_base_library_initv"

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local noundef zeroext i1 @_Z7odaberiiiiddb(i32 noundef %0, i32 noundef %1, i32 noundef %2, double noundef %3, double noundef %4, i1 noundef zeroext %5) #0 {
  %7 = alloca i1, align 1
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca double, align 8
  %12 = alloca double, align 8
  %13 = alloca i8, align 1
  store i32 %0, ptr %8, align 4
  store i32 %1, ptr %9, align 4
  store i32 %2, ptr %10, align 4
  store double %3, ptr %11, align 8
  store double %4, ptr %12, align 8
  %14 = zext i1 %5 to i8
  store i8 %14, ptr %13, align 1
  %15 = load i32, ptr %8, align 4
  %16 = load i32, ptr %10, align 4
  %17 = icmp sgt i32 %15, %16
  br i1 %17, label %18, label %19

18:                                               ; preds = %6
  store i1 true, ptr %7, align 1
  br label %22

19:                                               ; preds = %6
  %20 = load i8, ptr %13, align 1
  %21 = trunc i8 %20 to i1
  store i1 %21, ptr %7, align 1
  br label %22

22:                                               ; preds = %19, %18
  %23 = load i1, ptr %7, align 1
  ret i1 %23
}

; Function Attrs: mustprogress noinline norecurse nounwind optnone uwtable
define dso_local noundef i32 @main() #1 {
  %1 = alloca double, align 8
  %2 = alloca double, align 8
  store double 2.100000e+00, ptr %1, align 8
  store double 3.300000e+00, ptr %2, align 8
  %3 = load double, ptr %1, align 8
  %4 = load double, ptr %2, align 8
  %5 = call noundef zeroext i1 @_Z7odaberiiiiddb(i32 noundef 13, i32 noundef 5, i32 noundef 2003, double noundef %3, double noundef %4, i1 noundef zeroext true)
  %6 = load double, ptr %2, align 8
  %7 = load double, ptr %1, align 8
  %8 = call noundef zeroext i1 @_Z7odaberiiiiddb(i32 noundef 99, i32 noundef 100, i32 noundef 101, double noundef %6, double noundef %7, i1 noundef zeroext false)
  %9 = load double, ptr %2, align 8
  %10 = call noundef zeroext i1 @_Z7odaberiiiiddb(i32 noundef 1000, i32 noundef 1000, i32 noundef 1000, double noundef %9, double noundef 3.140000e+00, i1 noundef zeroext true)
  ret i32 0
}

attributes #0 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 17.0.0"}
