local function benchmark(name, func)
    local start = os.clock()
    func()
    local duration = os.clock() - start
    print(string.format("[%-20s]  %.3f seconds", name, duration))
end

-- 基准1：整数加法
local function int_arith()
    local sum = 0
    for i = 1, 1e8 do
        sum = sum + i
    end
end

-- 基准2：浮点运算
local function float_arith()
    local sum = 0.0
    for i = 1, 1e7 do
        sum = sum + math.sin(i) * math.cos(i)
    end
end

-- 基准3：表操作
local function table_ops()
    local t = {}
    for i = 1, 1e6 do
        t[i] = i
    end
    local sum = 0
    for i = 1, 1e6 do
        sum = sum + t[i]
    end
end

-- 基准4：递归
local function recurse(n)
    if n == 0 then return 0 end
    return 1 + recurse(n - 1)
end

-- 跑测试
benchmark("Integer Arithmetic", int_arith)
benchmark("Float Arithmetic", float_arith)
benchmark("Table Operations", table_ops)
benchmark("Recursion (Depth 5000)", function() recurse(5000) end)
