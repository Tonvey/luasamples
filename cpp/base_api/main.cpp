#include <iostream>
#include <lua.hpp>
using namespace std;

int array_test(lua_State *L)
{
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  into array_test" << endl;
    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    luaL_checktype(L, 1, LUA_TTABLE);

    // 方法 1
    {
        // 因为lua_next 的第1步会先从栈顶弹出一个key， 如果没值会出错，所以这里压个nil，让其不出错
        lua_pushnil(L);

        // lua_next(L, 1) =>   1 是 table在栈中的位置
        // 1. 先从栈顶弹出一个key （因为是数组，所以这个key就是序号了）
        // 2. 从栈指定位置的table中取一对 key-value， 先将key入栈，再将value入栈
        // 3. 如果第2步成功则返回非0值， 否则返回0, 且不向栈中压入任何值
        while (lua_next(L, 1) != 0)
        {
            cout << "key: " << lua_tonumber(L, -2) << "  value: " << lua_tostring(L, -1) << endl;

            // lua_next会把key弹掉， 所以这里只要弹掉value即可恢复栈
            lua_pop(L, 1);
        }
        lua_pop(L, 1);  // 弹出table
    }

    // 方法 2
    {
        //size_t n = lua_objlen(L, -1);
        //for (int i = 1; i <= n; ++i)
        //{
        //    // 索引号压栈
        //    lua_pushnumber(L, i);

        //    //  1. 上一步的num出栈（pop number） , 这里 num = i
        //    //  2. 通过这个num,获取索引号对应的值table[num]
        //    //  3. 把这个值table[num] 压栈 (push table[num] )
        //    lua_gettable(L, 1);

        //    //  获取这个值table[num]
        //    cout << lua_tostring(L, -1) << endl;

        //    // 出栈， 1 是出栈的数量
        //    lua_pop(L, 1);
        //}
        //lua_pop(L, 1);  // 弹出table
    }

    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    return 0;
}

int map_test(lua_State *L) {
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  into map_test" << endl;
    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    luaL_checktype(L, 1, LUA_TTABLE);

    // 方法 1
    {
        // 因为lua_next 的第1步会先从栈顶弹出一个key， 如果没值会出错，所以这里压个nil，让其不出错
        lua_pushnil(L);

        // lua_next(L, 1) =>   1 是 table在栈中的位置
        // 1. 先从栈顶弹出一个key
        // 2. 从栈指定位置的table中取一对 key-value， 先将key入栈，再将value入栈
        // 3. 如果第2步成功则返回非0值， 否则返回0, 且不向栈中压入任何值
        while (lua_next(L, 1) != 0) {
            cout << "key: " << lua_tostring(L, -2) << "  value: " << lua_tostring(L, -1) << endl;

            // lua_next会把key弹掉， 所以这里只要弹掉value即可恢复栈
            lua_pop(L, 1);
        }
        lua_pop(L, 1); // 弹出table
    }

    // 方法 2 （根key 获取 value）
//    {
//        lua_getfield(L, 1, "a");        // 获取到 table["a"] 的值， 压入栈顶
//        cout << "a => " << lua_tostring(L, -1) << endl;
//
//        lua_getfield(L, 1, "b");
//        cout << "b => " << lua_tostring(L, -1) << endl;
//
//        lua_getfield(L, 1, "c");
//        cout << "c => " << lua_tostring(L, -1) << endl;
//
//        lua_getfield(L, 1, "d");
//        cout << "d => " << lua_tostring(L, -1) << endl;
//
//        lua_pop(L, 5);  // 全部弹出
//    }

    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    return 0;
}

int checkType_test(lua_State *L) {
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  into checkType_test" << endl;
    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    // luaL_checktype ， 一旦类型不符合， 代码不会继续执行
    luaL_checktype(L, -1, LUA_TBOOLEAN);
    cout << "第1个参数类型检查通过" << endl;

    // lua_type ， 就算类型不符合， 代码也会继续执行
    int nType = lua_type(L, -2);
    if (nType != LUA_TNUMBER) {
        cout << "第2个参数类型不符合" << endl;
//        luaL_argerror(L, -2, "参数类型不符合");
    }

    lua_pop(L, 2);

    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    return 0;
}

int simple_test(lua_State *L)
{
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  into simple_test" << endl;
    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    // 获取lua脚本传过来的参数
    const char *name = lua_tostring(L, -2);
    //    size_t len;
    //    const char *name = lua_tolstring(L, -2, &len);
    lua_Integer age = lua_tointeger(L, -1);
    lua_pop(L, 2);

    cout << "name:" << name << "  age:" << age << endl;

    // lua脚本调用函数的返回值
    lua_pushinteger(L, 99);

    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    return 1;
}

int ret_test(lua_State *L) {
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  into ret_test" << endl;
    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    lua_pushstring(L, "张三");
    lua_pushnumber(L, 12);

    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    return 2;
}

int ret_table_test(lua_State *L) {
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  into ret_table_test" << endl;
    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    // 创建表，压栈
    lua_newtable(L);

    // 一对key  value 入栈
    // 压入key
    lua_pushstring(L, "name");
    // 压入value
    lua_pushstring(L, "张三");

    // 此时，表在栈底
    // 弹出 key  value 设置到表.  此时，表在栈顶了
    lua_settable(L, 1);

    //-------------------------------
    // 一对key  value 入栈
    // 压入key
    lua_pushstring(L, "age");
    // 压入value
    lua_pushinteger(L, 22);

    // 此时，表在栈底
    // 弹出 key  value 设置到表.  此时，表在栈顶了
    lua_settable(L, 1);


    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    return 1;
}

int getLuaVar_test(lua_State *L) {
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  into getLuaVar_test" << endl;
    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    lua_getglobal(L, "g_var1");
    lua_Number num = lua_tonumber(L, -1);
    cout << "g_var1 = " << num << endl;
    lua_pop(L, 1);

    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    return 0;
}

int set2LuaVar_test(lua_State *L) {
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  into set2LuaVar_test" << endl;
    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    lua_pushstring(L, "赵六");

    // 将栈顶位置设置为全局变量，并出栈
    lua_setglobal(L, "g_name");

    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    return 0;
}


int getLuaVar_table_test(lua_State *L) {
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  into getLuaVar_table_test" << endl;
    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    // 一层map
    {
        cout << "----------- 一层map ----------" << endl;

        lua_getglobal(L, "g_t1");
        {
            lua_getfield(L, -1, "name");  // name的值入栈
            const char *name = lua_tostring(L, -1);
            cout << "name = " << name << endl;
            lua_pop(L, 1);  // 弹掉 name

            lua_getfield(L, -1, "age");  // age的值入栈
            lua_Number age = lua_tonumber(L, -1);
            cout << "age = " << age << endl;
            lua_pop(L, 1);  // 弹掉 age
        }
        lua_pop(L, 1);  //  弹掉 g_t1

        cout << "当前栈上数量 = " << lua_gettop(L) << endl;
    }

    // 嵌套的map
    {
        cout << "----------- 嵌套的map ---------" << endl;

        lua_getglobal(L, "g_t2");
        {
            // 因为lua_next 的第1步会先从栈顶弹出一个key， 如果没值会出错，所以这里压个nil，让其不出错
            lua_pushnil(L);

            // lua_next(L, 1) =>   1 是 table在栈中的位置
            // 1. 先从栈顶弹出一个key
            // 2. 从栈指定位置的table中取一对 key-value， 先将key入栈，再将value入栈
            // 3. 如果第2步成功则返回非0值， 否则返回0, 且不向栈中压入任何值
            while (lua_next(L, 1) != 0) {
                lua_Number key = lua_tonumber(L, -2);
                cout << "key: " << key << endl;

                // 取value的值， 这里的value就是子table, 在栈顶
                {
                    lua_getfield(L, -1, "name");  // 子table中name的值入栈
                    cout << "value: " << lua_tostring(L, -1) << endl;
                    lua_pop(L, 1);  // 弹掉 name

                    lua_getfield(L, -1, "age");   // 子table中age的值入栈
                    cout << "age: " << lua_tonumber(L, -1) << endl;
                    lua_pop(L, 1); // 弹掉 age
                }

                // lua_next会把key弹掉， 所以这里只要弹掉value（子table）即可恢复栈
                lua_pop(L, 1);
                cout << "**********" << endl;
            }
        }
        lua_pop(L, 1); // 弹掉 g_t2
        cout << "当前栈上数量 = " << lua_gettop(L) << endl;
    }

    return 0;
}

int setLuaVar_table_test(lua_State *L) {
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  into setLuaVar_table_test" << endl;
    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    // 创建表，压栈
    lua_newtable(L);

    // 一对key  value 入栈
    // 压入key
    lua_pushstring(L, "name");
    // 压入value
    lua_pushstring(L, "张三");

    // 此时，表在栈底
    // 弹出 key  value 设置到表.  此时，表在栈顶了
    lua_settable(L, 1);

    //-------------------------------
    // 一对key  value 入栈
    // 压入key
    lua_pushstring(L, "age");
    // 压入value
    lua_pushinteger(L, 22);

    // 此时，表在栈底
    // 弹出 key  value 设置到表.  此时，表在栈顶了
    lua_settable(L, 1);

    // 将此表设置为全局变量
    lua_setglobal(L, "g_varTable");

    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    return 0;
}

void callLuaFunc_simple(lua_State *L) {
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  into callLuaFunc_simple" << endl;
    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    const string luaFuncName = "luaSimpleFunc";
    lua_getglobal(L, luaFuncName.c_str());  // 获取lua函数
    if (lua_pcall(L, 0, 0, 0) != 0)   // 调用失败
    {
        // 失败会产生错误，这个错误会压栈。 这里把它出栈，以免内存泄露
        cout << "call " << luaFuncName << " failed ! error = " << lua_tostring(L, -1) << endl;
        lua_pop(L, 1);
    }

    cout << "当前栈上数量 = " << lua_gettop(L) << endl;
}

void callLuaFunc_params_ret(lua_State *L) {
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  into callLuaFunc_params_ret" << endl;
    cout << "当前栈上数量 = " << lua_gettop(L) << endl;

    const char* luaErrorFuncName = "fError";
    lua_getglobal(L, luaErrorFuncName);   // 获取lua错误处理函数

    const char* luaFuncName = "luaParamsAndRetFunc";
    lua_getglobal(L, luaFuncName);  // 获取lua函数

    lua_pushstring(L, "张三");   // 参数1
    lua_pushinteger(L, 23);     // 参数2

    lua_newtable(L);               // 参数3
    // 表在栈中的位置
    int tIdx =  lua_gettop(L);
    // 压入key
    lua_pushstring(L, "score");
    // 压入value
    lua_pushnumber(L, 91.5);
    // 弹出 key  value 设置到表.  此时，表在栈顶了
    lua_settable(L, tIdx);

    // 别忘了设置： 参数个数 、 返回值个数 、 错误处理函数在栈位置
    if (lua_pcall(L, 3, 2, -5) != 0)   // 调用失败
    {
        cout << "call " << luaFuncName << " failed ! error = " << lua_tostring(L, -2) << endl;
        // 失败会产生错误，这个错误会压栈。 这里把它出栈，以免内存泄露
        lua_pop(L, 1);
    } else {
        // 获取返回值1
        cout << "ret1 = " << lua_tostring(L, -2) << endl;

        // 获取返回值2 (table)
        // 这里演示直接获取字段值。 如要全表遍历，参考之前的代码
        lua_getfield(L, -1, "name");
        cout << "name = " << lua_tostring(L, -1) << endl;
        lua_pop(L, 1);
        lua_getfield(L, -1, "age");
        cout << "age = " << lua_tointeger(L, -1) << endl;
        lua_pop(L, 1);

        // 这里把它出栈，以免内存泄露
        lua_pop(L, 2);    //  有2个返回值
    }

    // 弹出错误处理函数，以免内存泄露
    lua_pop(L, 1);

    cout << "当前栈上数量 = " << lua_gettop(L) << endl;
}

int main()
{
    // 创建状态机
    lua_State *L = luaL_newstate();

    // 打开基本库
    luaL_openlibs(L);

    // 获取lua传递过来的普通参数测试 (给lua写的函数)
    lua_register(L, "simple_test", simple_test);

    // 获取lua传递过来的array参数测试 (给lua写的函数)
    lua_register(L, "array_test", array_test);

    // 获取lua传递过来的map参数测试 (给lua写的函数)
    lua_register(L, "map_test", map_test);

    // lua传递过来的参数类型检查测试 (给lua写的函数)
    lua_register(L, "checkType_test", checkType_test);

    // lua调用C++函数的返回值测试 (给lua写的函数)
    lua_register(L, "ret_test", ret_test);

    // lua调用C++函数的返回值（table）测试 (给lua写的函数)
    lua_register(L, "ret_table_test", ret_table_test);

    // 给lua传递c++全局变量值 (lua可用的C++全局变量)
    // set2LuaVar_test(L);

    // 给lua传递c++全局变量值（table） (lua可用的C++全局变量)
    // setLuaVar_table_test(L);

    // -------- 调用脚本前 ---------
    luaL_dofile(L, "./test1.lua");

    // -------- 调用脚本后 ---------

    // c++获取lua的全局变量值 (C++可用的lua全局变量)
    //getLuaVar_test(L);

    //// c++获取lua的全局变量值（table） (C++可用的lua全局变量)
    //getLuaVar_table_test(L);

    //// c++调用lua函
    //callLuaFunc_simple(L);

    //// c++调用lua函数(带参数和返回值)
    //callLuaFunc_params_ret(L);

    // 关闭
    lua_close(L);

    cout << " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> end <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";

    return 0;
}
