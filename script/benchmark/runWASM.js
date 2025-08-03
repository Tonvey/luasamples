// 这个脚本用来执行通过 benchmark.ts 编译的 WebAssembly 模块
// node runWASM.js
const fs = require("fs");
const { performance } = require("perf_hooks");

(async () => {
  const wasmBuffer = fs.readFileSync("benchmark.wasm");

  const imports = {
    env: {
      abort(msgPtr, filePtr, line, col) {
        console.error("Abort called at", line, col);
      },
      // 如果你关闭 runtime，可以去掉
    }
  };

  const { instance } = await WebAssembly.instantiate(wasmBuffer, imports);
        
  // 调用导出函数
  const { intArith, floatArith, tableOps, recurse } = instance.exports;

  function benchmark(name, fn) {
    const t0 = performance.now();
    const result = fn();
    const t1 = performance.now();
    console.log(`[${name.padEnd(24)}] ${(t1 - t0).toFixed(2)} ms  Result: ${result}`);
  }

  benchmark("Integer Arithmetic", intArith);
  benchmark("Float Arithmetic", floatArith);
  benchmark("Table Operations", tableOps);
  benchmark("Recursion (5000)", () => recurse(5000));
})();