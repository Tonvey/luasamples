-- metatable 测试

print("version: " .. _VERSION)

do
    print("================================================")
    print("print default metatable")
    print(getmetatable("string"))
    print(getmetatable(1.0))

    local t = {}
    print(getmetatable(t))  -- nil, no metatable set
    local t1 = {}
    setmetatable(t ,t1)
    print(getmetatable(t))  -- t1, metatable set to t1
end

do
    print("================================================")
    print("测试元表的基本操作")
    -- 写一个能够测试元表的例子，要求将加减乘除取模，^等操作都实现
    local mt = {
        __add = function(a, b)
            return a.value + b.value
        end,
        __sub = function(a, b)
            return a.value - b.value
        end,
        __mul = function(a, b)
            return a.value * b.value
        end,
        __div = function(a, b)
            return a.value / b.value
        end,
        __mod = function(a, b)
            return a.value % b.value
        end,
        __pow = function(a, b)
            return a.value ^ b.value
        end,
        __tostring = function(a)
            return "Value: " .. a.value
        end

        -- 可以添加更多的元方法，如 __eq, __lt, __le 等
    }

    local a = {value = 10}
    setmetatable(a, mt)
    local b = {value = 5}
    setmetatable(b, mt)
    print(a + b)  -- 输出15
    print(a - b)  -- 输出5
    print(a * b)  -- 输出50
    print(a / b)  -- 输出2
    print(a % b)  -- 输出0
    print(a ^ b)  -- 输出100000
    print(a)      -- 输出"Value: 10"


    print("================================================")
    print("测试元表的 __index 方法")
    -- 测试元表的 __index 方法
    local mt2 = {
        __index = function(t, k)
            if k == "x" then
                return 10
            elseif k == "y" then
                return 20
            elseif k == "z" then
                return 30
            else
                return nil  -- 返回 nil 如果没有找到
            end
        end
    }

    local a = setmetatable({}, mt2)
    print(a.x)  -- 输出10
    print(a.y)  -- 输出20
    print(a.z)  -- 输出30
    print(a.w)  -- 输出nil, w不存在

    print("================================================")
    print("测试元表的 __index 是一个表")
    -- 测试当__index是一个表而不是函数的时候
    local mt4 = {
        x = 10,
        y = 20,
        z = 30
    }
    local a = setmetatable({}, {__index = mt4})
    print(a.x)  -- 输出10
    print(a.y)  -- 输出20
    print(a.z)  -- 输出30
    print(a.w)  -- 输出nil, w不存在

    print("================================================")
    print("测试元表的 __newindex 方法")
    -- 测试元表的 __newindex 方法
    local mt3 = {
        __newindex = function(t, k, v)
            if k == "x" then
                rawset(t, k, v)  -- 使用 rawset 来设置值
            elseif k == "y" then
                rawset(t, k, v)
            elseif k == "z" then
                rawset(t, k, v)
            else
                error("Invalid key: " .. k)  -- 抛出错误，如果键不是 x, y, z
            end
        end
    }

    local a = setmetatable({}, mt3)
    a.x = 10
    a.y = 20
    a.z = 30
    print(a.x)  -- 输出10
    print(a.y)  -- 输出20
    print(a.z)  -- 输出30
    -- a.w = 40  -- 如果取消注释，将抛出错误 "



end