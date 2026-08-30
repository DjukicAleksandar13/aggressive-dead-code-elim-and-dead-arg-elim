; ModuleID = 'DAE_Test3.ll'
source_filename = "DAE_Test3.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

module asm ".globl _ZSt21ios_base_library_initv"

; Function Attrs: mustprogress noinline norecurse nounwind optnone uwtable
define dso_local noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 10, ptr %1, align 4
  store i32 2, ptr %2, align 4
  %3 = load i32, ptr %1, align 4
  %4 = load i32, ptr %2, align 4
  %5 = add nsw i32 %3, %4
  %6 = load i32, ptr %1, align 4
  %7 = load i32, ptr %2, align 4
  call void @_Z1fiii.3(i32 %6, i32 %7)
  ret i32 0
}

define i32 @_Z6dodaj2ii.1(i32 %0) {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %4 = load i32, ptr %2, align 4
  %5 = add nsw i32 %4, 2
  ret i32 %5
}

define void @_Z1giii.2(i32 %0, i32 %1) {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %5, align 4
  %8 = load i32, ptr %3, align 4
  %9 = load i32, ptr %5, align 4
  %10 = add nsw i32 %8, %9
  store i32 %10, ptr %6, align 4
  %11 = load i32, ptr %3, align 4
  %12 = load i32, ptr %3, align 4
  %13 = load i32, ptr %5, align 4
  %14 = sub nsw i32 %12, %13
  %15 = call i32 @_Z6dodaj2ii.1(i32 %11)
  store i32 %15, ptr %7, align 4
  ret void
}

define void @_Z1fiii.3(i32 %0, i32 %1) {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 %0, ptr %4, align 4
  store i32 %1, ptr %5, align 4
  %6 = load i32, ptr %4, align 4
  %7 = load i32, ptr %5, align 4
  %8 = sub nsw i32 %6, %7
  %9 = load i32, ptr %4, align 4
  %10 = load i32, ptr %5, align 4
  call void @_Z1giii.2(i32 %8, i32 %10)
  ret void
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
