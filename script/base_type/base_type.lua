-- 测试lua各种基础类型

print("version: " .. _VERSION)
print("type(_VERSION): " .. type(_VERSION))

local iValue = 10 
local fValue = 10.2 
local strValue = "Hello World" 
local funcValue = print 
local bValue = true 
local nilValue = nil 
local tbValue = {} 

print("iValue:"..type(iValue))
print("fValue:"..type(fValue))
print("strValue:"..type(strValue))
print("funcValue:"..type(funcValue))
print("bValue:"..type(bValue))
print("nilValue:"..type(nilValue))
print("tbValue:"..type(tbValue))
print("io.stdin:"..type(io.stdin))
print("type:"..type(type))

print("================================================")
print("String Test : ")

local page = [[ 
 <html xmlns="http://www.w3.org/1999/xhtml"> 
      <head> 
           <title>xxxx</title> 
      </head> 
      <body> 
      </body> 
 </html> 
 ]] 
print(page) 
print("len of page is : "..#page)   -- 获取字符串的长度

print("================================================")
print("Boolean Test : ")
local zero = 0
if zero then
    print("zero is true")
else
    print("zero is false")
end

if nilValue then
    print("nilValue is true")
else
    print("nilValue is false")
end

print("================================================")
print("Table Test : ")
do
    local a = {}
    local k = "x"
    local tbKey = { "x", 20 };
    a[k] = 10
    a[20] = "great"
    a[tbKey] = 30
    print(a["x"])    -- 输出10
    print(a.x)       -- 输出10
    print(a[tbKey])  -- 输出30
    
    k = 20
    print(a[k])      -- 输出"great"

    local a = {} 
    a[1000] = 1 
    print(#a)        -- 输出0，因为索引不是从1开始的

    local maxn = 0
    for k, v in pairs(a) do
        if type(k) == "number" and k > maxn then maxn = k end
    end
    print(maxn)

    local days = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    }

    print(days[4])  -- 输出"Wednesday"

    local a = {
        x = 10,
        y = 20,
        z = 30
    }
    print(a.y)  -- 输出20


    local polyline = {
        color = "red",
        thickness = 2,
        npoints = 3,
        {x = 0, y = 0},     -- polyline[1]
        {x = 10, y = 10},   -- polyline[2]
        {x = 20, y = 20}    -- polyline[3]
    }

    local opnames = {
        ["+"] = "add",
        ["-"] = "sub",
        ["*"] = "mul",
        ["/"] = "div"
    }

    print(opnames["-"])  -- 输出"add"


    local t = {10,print,x=12,k = "hi", 30}
    for k,v in pairs(t) do
        print(k,v)
    end

    for k,v in ipairs(t) do
        print(k,v)
    end
end


print("================================================")
print("function Test : ")
do
    function maximum(a)
        local mi =1
        local m = a[mi]
        for i = 1 , #a do
            if a[i] > m then
                mi = i; m = a[i]
            end
        end
        return m ,mi
    end

    local m, mi = maximum({8,10,23,12,5})
    print("maximum value is: " .. m .. ", index is: " .. mi)  

    function foo0() end
    function foo1() return "a" end
    function foo2() return "a", "b" end

    local x,y
    x,y = foo0()        -- x=nil, y=nil
    x,y = foo1()        -- x="a", y=nil
    x,y,z = foo2()      -- x="a", y="b", z=nil
end