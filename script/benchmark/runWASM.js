// 这个脚本用来执行通过 benchmark.ts 编译的 WebAssembly 模块
// node runWASM.js
const fs = require("fs");
const { performance } = require("perf_hooks");

(async () => {
  const bytes = fs.readFileSync("./benchmark.wasm");
  const module = await WebAssembly.instantiate(bytes, {});
  const { intArith, floatArith, tableOps, recurse } = module.instance.exports;

  function benchmark(name, fn) {
    const start = performance.now();
    const result = fn();
    const duration = (performance.now() - start) / 1000;
    console.log(`[${name.padEnd(20)}] ${duration.toFixed(3)}s  Result: ${result}`);
  }

  benchmark("Integer Arithmetic", intArith);
  benchmark("Float Arithmetic", floatArith);
  benchmark("Table Operations", tableOps);
  benchmark("Recursion (5000)", () => recurse(5000));
})();
