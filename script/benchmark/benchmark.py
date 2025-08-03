#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import math
import time

def benchmark(name, func):
    start = time.perf_counter()
    result = func()
    duration = time.perf_counter() - start
    print(f"[{name:<24}] {duration:.3f} seconds  Result: {result}")

# 整数加法
def int_arith():
    sum_ = 0
    for i in range(1, 100_000_001):
        sum_ += i
    return sum_

# 浮点运算
def float_arith():
    sum_ = 0.0
    for i in range(1, 10_000_001):
        sum_ += math.sin(i) * math.cos(i)
    return sum_

# 列表操作
def table_ops():
    arr = [i for i in range(1_000_000)]
    return sum(arr)

# 递归测试
def recurse(n):
    if n == 0:
        return 0
    return 1 + recurse(n - 1)

if __name__ == "__main__":
    benchmark("Integer Arithmetic", int_arith)
    benchmark("Float Arithmetic", float_arith)
    benchmark("Table Operations", table_ops)
    benchmark("Recursion (Depth 5000)", lambda: recurse(5000))
