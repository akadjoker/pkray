#pragma once



static std::map<std::string, NativeFuncC> coreFunctions =
{

    {"setTargetFPS(fps:int)", [](VM *vm, ArgsView args) -> PyVar
    {
        int fps = py_cast<int>(vm, args[0]);
        SetTargetFPS(fps);
        return py_var(vm, 0);
    }},
    {"getFrameTime()", [](VM *vm, ArgsView args) -> PyVar
    {
        return py_var(vm, GetFrameTime());
    }},

    {"getElapsedTime()", [](VM *vm, ArgsView args) -> PyVar
    {
        return py_var(vm, GetTime());
    }},

    {"getFPS()", [](VM *vm, ArgsView args) -> PyVar
    {
        return py_var(vm, GetFPS());
    }},

    {"random(min:int,max:int)", [](VM *vm, ArgsView args) -> PyVar
    {
        int min = py_cast<int>(vm, args[0]);
        int max = py_cast<int>(vm, args[1]);

        return py_var(vm, GetRandomValue(min,max));
    }}
};

static std::map<std::string, NativeFuncC> windowFunctions =
    {

        {"init(w:int,h:int,title:str)", [](VM *vm, ArgsView args) -> PyVar
         {
            if (IsReady) return py_var(vm, 0);
            
             int width = py_cast<int>(vm, args[0]);
             int height = py_cast<int>(vm, args[1]);
             const char* title = py_cast<const char*>(vm, args[2]);

             InitWindow(width, height, title);
             IsReady = true;

             return py_var(vm, 1);
         }},
        {"shouldClose()", [](VM *vm, ArgsView args) -> PyVar
         {
             if (!IsReady) return py_var(vm, 0);
             return py_var(vm, WindowShouldClose());
         }},
        {"close()", [](VM *vm, ArgsView args) -> PyVar
         {
             if (!IsReady) return py_var(vm, 0);
             AssetManager::Instance().Clear();
             AssetManager::Instance().Free();
             CloseWindow();
             IsReady = false;
             return py_var(vm, 1);
         }},
        {"getWidth()", [](VM *vm, ArgsView args) -> PyVar
         {
             return py_var(vm, GetScreenWidth());
         }},
        {"getHeight()", [](VM *vm, ArgsView args) -> PyVar
         {
             return py_var(vm, GetScreenHeight());
         }}};

inline void RegisterWindowFunctions(VM* vm)
{
     PyObject* mod = vm->new_module("window");
    //  vm->bind(mod, "init(w:int,h:int,title:str)", [](VM *vm, ArgsView args) -> PyVar
    //  {
    //      return py_var(vm, 0);
    //  });

    //  vm->bind(mod, "close()", [](VM *vm, ArgsView args) -> PyVar
    //  {
    //      return py_var(vm, 0);
    //  });


    for (const auto& func : windowFunctions) 
    {
         vm->bind(mod, func.first.c_str(), func.second);
       
    }
    

 }

 inline void RegisterCoreFunctions(VM* vm)
 {
     PyObject* mod = vm->new_module("core");
    for (const auto& func : coreFunctions) 
    {
         vm->bind(mod, func.first.c_str(), func.second);
       
    }
 }