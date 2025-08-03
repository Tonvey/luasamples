#!/usr/bin/env ruby

# 如果测试普通Ruby，使用 ：ruby benchmark_ruby.rb
# 如果想测试jit，应该使用 sdk install ruby truffleruby 之后再ruby benchmark_ruby.rb

require 'benchmark'

def int_arith
  sum = 0
  1.upto(100_000_000) { |i| sum += i }
  sum
end

def float_arith
  sum = 0.0
  1.upto(10_000_000) { |i| sum += Math.sin(i) * Math.cos(i) }
  sum
end

def table_ops
  arr = Array.new(1_000_000) { |i| i }
  arr.sum
end

def recurse(n)
  return 0 if n == 0
  1 + recurse(n - 1)
end

Benchmark.bm(30) do |x|
  x.report("Integer Arithmetic")     { puts "Result: #{int_arith}" }
  x.report("Float Arithmetic")       { puts "Result: #{float_arith}" }
  x.report("Table Operations")       { puts "Result: #{table_ops}" }
  x.report("Recursion (Depth 5000)") { puts "Result: #{recurse(5000)}" }
end
