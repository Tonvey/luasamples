-- 面向对象测试

print("version: " .. _VERSION)

do
    local Account = {balance = 0}
    function Account.withdraw(v)
        Account.balance = Account.balance - v
    end

    Account.withdraw(100)
end

do
    print("================================================")
    print("最基本的self测试 : ")
    local Account = {balance = 0}
    function Account.withdraw(self,v)
        self.balance = self.balance - v
    end

    local a2 = {balance = 1000 , withdraw = Account.withdraw}
    a2.withdraw(a2, 100)
    print(a2.balance)   -- 输出900
    a2:withdraw(100)    -- 使用冒号调用
    print(a2.balance)   -- 输出800
end


do
    -- 使用metatable实现面向对象
    print("================================================")
    print("使用meta table实现 : ")
    local Account = {balance = 0}
    function Account:withdraw(v)
        if v > self.balance then
            error "insufficient funds"
        end
        self.balance = self.balance - v
    end
    function Account:deposit(v)
        self.balance = self.balance + v
    end

    local mt = { __index = Account }  -- 设置元表
    function Account:new(o)
        o = o or {}
        setmetatable(o, mt)  -- 设置元表
        return o
    end

    local a = Account:new{balance = 1000}
    a:deposit(500)
    a:withdraw(100)
    print(a.balance)  -- 输出1400

end

do
    -- 继承
    print("================================================")
    print("继承测试 : ")

    local Account = {balance = 0}
    function Account:withdraw(v)
        if v > self.balance then
            error "insufficient funds"
        end
        self.balance = self.balance - v
    end
    function Account:deposit(v)
        self.balance = self.balance + v
    end

    function Account:new(o)
        o = o or {}
        self.__index = self
        setmetatable(o, self)  -- 设置元表
        return o
    end
    local SpecialAccount = Account:new()  -- 继承Account

    function SpecialAccount:withdraw(v)
        if v - self.balance > self:getLimit() then
            error "insufficient funds"
        end
        self.balance = self.balance - v
    end

    function SpecialAccount:getLimit()
        return self.limit or 0
    end

    local s = SpecialAccount:new{limit = 1000}
    print(s:getLimit())  -- 输出1000
    s:deposit(2000)
    print(s.balance)  -- 输出2000
    s:withdraw(1500)
    print(s.balance)  -- 输出500
    -- s:withdraw(3000)  -- 抛出错误 "insufficient funds"

end


do
    -- 一个生产环境中的例子Qdazzle
    print("================================================")
    print("一个生产环境中的例子 : ")
    --保存类类型的虚表
    local _class = {}
     
    function BaseClass(super)
        -- 生成一个类类型
        local class_type = {}
        -- 在创建对象的时候自动调用
        class_type.__init = false
        class_type.__delete = false
        class_type.super = super
        class_type.New = function(...)
            -- 生成一个类对象
            local obj = {}
            obj._class_type = class_type
    
            -- 在初始化之前注册基类方法
            setmetatable(obj, { __index = _class[class_type] })
    
            -- 调用初始化方法
            do
                local create 
                create = function(c, ...)
                    if c.super then
                        create(c.super, ...)
                    end
                    if c.__init then
                        c.__init(obj, ...)
                    end
                end
    
                create(class_type, ...)
            end
    
            -- 注册一个delete方法
            obj.DeleteMe = function(self)
                local now_super = self._class_type 
                while now_super ~= nil do	
                    if now_super.__delete then
                    	now_super.__delete(self)
                    end
                    now_super = now_super.super
                end
            end
    
            return obj
        end
    
        local vtbl = {}
        _class[class_type] = vtbl	
        
        setmetatable(class_type, {__newindex =
            function(t,k,v)
                vtbl[k] = v
            end
            , 
            __index = vtbl, --For call parent method
        })
        
        if super then
            setmetatable(vtbl, {__index =
                function(t,k)
                    local ret = _class[super][k]
                    --do not do accept, make hot update work right!
                    --vtbl[k] = ret
                    return ret
                end
            })
        end
        
        return class_type
    end
    

    local Account = BaseClass()
    Account.balance = 0
    function Account:withdraw(v)
        if v > self.balance then
            error "insufficient funds"
        end
        self.balance = self.balance - v
    end
    function Account:deposit(v)
        self.balance = self.balance + v
    end


    local SpecialAccount = BaseClass(Account)  -- 继承Account
    local s = SpecialAccount:New()
    print(s.balance)
    s:deposit(2000)
    print(s.balance)  -- 输出2000
    s:withdraw(1500)
    print(s.balance)  -- 输出500
end