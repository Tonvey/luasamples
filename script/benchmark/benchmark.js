// 这个脚本跟lua脚本的benchmark.lua功能类似,主用来跑在v8或者quickjs上面对比验证性能
// v8可以这么测： node --expose-gc benchmark.js
// quickjs可以这么测： qjs benchmark.js
// quickjs没有jit比较拉胯，可以使用AOT
//      qjsc -o benchmark.c -c benchmark.js     # 生成 C 源码，包含字节码
//      gcc -o hello hello.c -lquickjs   # 编译为可执行文件
function benchmark(name, func) {
    const start = performance.now();
    func();
    const duration = (performance.now() - start) / 1000;
    console.log(`[${name.padEnd(20)}] ${duration.toFixed(3)} seconds`);
}

// 基准1：整数加法
function intArith() {
    let sum = 0;
    for (let i = 1; i <= 1e8; i++) {
        sum += i;
    }
}

// 基准2：浮点运算
function floatArith() {
    let sum = 0.0;
    for (let i = 1; i <= 1e7; i++) {
        sum += Math.sin(i) * Math.cos(i);
    }
}

// 基准3：表操作（对象/数组）
function tableOps() {
    const arr = new Array(1e6);
    for (let i = 0; i < 1e6; i++) {
        arr[i] = i;
    }
    let sum = 0;
    for (let i = 0; i < 1e6; i++) {
        sum += arr[i];
    }
}

// 基准4：递归
function recurse(n) {
    if (n === 0) return 0;
    return 1 + recurse(n - 1);
}

// 跑测试
benchmark("Integer Arithmetic", intArith);
benchmark("Float Arithmetic", floatArith);
benchmark("Table Operations", tableOps);
benchmark("Recursion (Depth 5000)", () => recurse(5000));
