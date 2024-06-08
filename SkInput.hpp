#pragma once

static std::map<std::string, NativeFuncC> keyFunctions =
    {
        {"pressed(key:int)", [](VM *vm, ArgsView args) -> PyVar
         {
             int key = py_cast<int>(vm, args[0]);
             return py_var(vm, IsKeyPressed(key));
         }},

        {"released(key:int)", [](VM *vm, ArgsView args) -> PyVar
         {
             int key = py_cast<int>(vm, args[0]);
             return py_var(vm, IsKeyReleased(key));
         }},

        {"down(key:int)", [](VM *vm, ArgsView args) -> PyVar
         {
             int key = py_cast<int>(vm, args[0]);
             return py_var(vm, IsKeyDown(key));
         }},

        {"up(key:int)", [](VM *vm, ArgsView args) -> PyVar
         {
             int key = py_cast<int>(vm, args[0]);
             return py_var(vm, IsKeyUp(key));
         }},

};

static std::map<std::string, NativeFuncC> mouseFunctions =
    {
        {"pressed(button:int)", [](VM *vm, ArgsView args) -> PyVar
         {
             int button = py_cast<int>(vm, args[0]);
             return py_var(vm, IsMouseButtonPressed(button));
         }},

        {"released(button:int)", [](VM *vm, ArgsView args) -> PyVar
         {
             int button = py_cast<int>(vm, args[0]);
             return py_var(vm, IsMouseButtonReleased(button));
         }},

        {"down(button:int)", [](VM *vm, ArgsView args) -> PyVar
         {
             int button = py_cast<int>(vm, args[0]);
             return py_var(vm, IsMouseButtonDown(button));
         }},

        {"up(button:int)", [](VM *vm, ArgsView args) -> PyVar
         {
             int button = py_cast<int>(vm, args[0]);
             return py_var(vm, IsMouseButtonUp(button));
         }},

};

inline void RegisterKeyboardFunctions(VM* vm)
{
    PyObject* mod = vm->new_module("keyboard");
   for (const auto& func : keyFunctions) 
   {
        vm->bind(mod, func.first.c_str(), func.second);
      
   }
}


inline void RegisterMouseFunctions(VM* vm)
{
    PyObject* mod = vm->new_module("mouse");
   for (const auto& func : mouseFunctions) 
   {
        vm->bind(mod, func.first.c_str(), func.second);
      
   }
}
