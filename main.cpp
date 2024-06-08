#include "pch.hpp"


 #include <pocketpy.h>

static bool IsReady = false;
  

using namespace pkpy;
#include "SkUtils.hpp"
#include "SkAssets.hpp"
#include "SkGraphics.hpp"
#include "SkInput.hpp"
#include "SkRay.hpp"

 





std::string readFile(const std::string& filePath) 
{
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


int main(int cv, char *argv[])
{
   

    VM* vm = new VM(true);
    RegisterWindowFunctions(vm);
    RegisterCoreFunctions(vm);
    RegisterGraphicsFunctions(vm);
    RegisterAssetsFunctions(vm);
    RegisterKeyboardFunctions(vm);
    RegisterMouseFunctions(vm);

    try 
    {
    
    if (cv > 1)
    {
        if (FileExists(argv[1]))
        {
            std::string code = readFile(argv[1]);
            vm->exec(code);
        }
    } else 
    {
        std::string code = readFile("main.py");
        vm->exec(code);
    }
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
    }

    delete vm;
    

    return 0;
}
