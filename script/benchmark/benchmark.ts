// benchmark.ts
// 用于AssemblyScript和luajit等形成对比
// npm install -g assemblyscript
// asc benchmark.ts -b benchmark.wasm --optimize --noAssert
// 你会得到：
//    benchmark.wasm
//    （可选）benchmark.wat - 可读的 WebAssembly 文本格式
// 最后使用runWASM.js脚本来运行这个WASM模块

export function intArith(): i64 {
  let sum: i64 = 0;
  for (let i: i64 = 1; i <= 1e8; i++) {
    sum += i;
  }
  return sum;
}

export function floatArith(): f64 {
  let sum: f64 = 0.0;
  for (let i: i32 = 1; i <= 1e7; i++) {
    sum += Mathf.sin(f64(i)) * Mathf.cos(f64(i));
  }
  return sum;
}

export function tableOps(): i64 {
  const size = 1_000_000;
  const arr = new Array<i32>(size);
  for (let i = 0; i < size; i++) {
    arr[i] = i;
  }
  let sum: i64 = 0;
  for (let i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum;
}

export function recurse(n: i32): i32 {
  if (n == 0) return 0;
  return 1 + recurse(n - 1);
}
