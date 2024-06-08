#pragma once

class Graphics
{
public:
    static Graphics &Instance()
    {
        static Graphics instance;
        return instance;
    }

    void SetColor(unsigned int r, unsigned int g, unsigned int b)
    {
        mDefaultColor.r = r;
        mDefaultColor.g = g;
        mDefaultColor.b = b;
    }

    void SetAlpha(unsigned int a)
    {
        mDefaultColor.a = a;
    }

    void SetFont(unsigned int id)
    {
        mDefaultFont = AssetManager::Instance().GetFont(id);
    }

    void Circle(float x, float y, float radius, bool mIsLine)
    {
        if (!IsReady)
            return;
        if (mIsLine)
        {
            DrawCircleLines(x, y, radius, mDefaultColor);
        }
        else
        {
            DrawCircle(x, y, radius, mDefaultColor);
        }
    }

    void Line(float x1, float y1, float x2, float y2)
    {
        if (!IsReady)
            return;
        DrawLine(x1, y1, x2, y2, mDefaultColor);
    }

    void Rect(float x, float y, float width, float height, bool mIsLine)
    {
        if (!IsReady)
            return;
        if (mIsLine)
        {
            Rectangle r;
            r.x = x;
            r.y = y;
            r.width = width;
            r.height = height;
            DrawRectangleLinesEx(r, mlineThickness, mDefaultColor);
        }
        else
        {
            DrawRectangle(x, y, width, height, mDefaultColor);
        }
    }

    void Ring(float x, float y, float innerRadius, float outerRadius, float startAngle, float endAngle, bool mIsLine)
    {
        if (!IsReady)
            return;
        Vector2 center;
        center.x = x;
        center.y = y;

        if (mIsLine)
        {
            DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, mSegments, mDefaultColor);
        }
        else
        {
            DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, mSegments, mDefaultColor);
        }
    }
    void RectangleRounded(float x, float y, float width, float height, float rounding, bool mIsLine)
    {
        if (!IsReady)
            return;
        Rectangle r;
        r.x = x;
        r.y = y;
        r.width = width;
        r.height = height;

        if (mIsLine)
        {
            DrawRectangleRoundedLines(r, rounding, mSegments, mlineThickness, mDefaultColor);
        }
        else
        {
            DrawRectangleRounded(r, rounding, mSegments, mDefaultColor);
        }
    }

    // DrawEllipse

    void Ellipse(float x, float y, float radiusx, float radiusy, bool mIsLine)
    {
        if (!IsReady)
            return;
        if (mIsLine)
        {
            DrawEllipseLines(x, y, radiusx, radiusy, mDefaultColor);
        }
        else
        {
            DrawEllipse(x, y, radiusx, radiusy, mDefaultColor);
        }
    }
    void Point(float x, float y)
    {
        if (!IsReady)
            return;
        DrawPixel(x, y, mDefaultColor);
    }

    void Text(float x, float y, const char *text)
    {
        if (!IsReady)
            return;
        DrawText(text, x, y, mTextSize, mDefaultColor);
    }

    void SetLineThickness(float thickness)
    {
        if (!IsReady)
            return;
        mlineThickness = thickness;
    }

    void SetTextSize(int size)
    {
        if (!IsReady)
            return;
        mTextSize = size;
    }

    void SetSegments(int segments)
    {
        mSegments = segments;
    }

    void Begin()
    {
        if (!IsReady)
            return;
        BeginMode2D(mCamera);
    }

    void End()
    {
        if (!IsReady)
            return;
        EndMode2D();
    }
    void SetViewPosition(float x, float y)
    {
        mCamera.target.x = x;
        mCamera.target.y = y;
    }

    void SetViewZoom(float value)
    {
        mCamera.zoom = value;
    }

    void SetViewRotation(float value)
    {
        mCamera.rotation = value;
    }

    void SetViewCenter(float x, float y)
    {
        mCamera.offset.x = x;
        mCamera.offset.y = y;
    }

    void Render(unsigned int id, float x, float y)
    {
        if (!IsReady)
            return;
        Texture2D texture = AssetManager::Instance().GetTexture(id);
        DrawTexture(texture, x, y, mDefaultColor);
    }
    void Render(unsigned int id, float x, float y, float scale, float rotation)
    {
        if (!IsReady)
            return;
        Texture2D texture = AssetManager::Instance().GetTexture(id);
        Vector2 center;
        center.x = x;
        center.y = y;
        DrawTextureEx(texture, center, rotation, scale, mDefaultColor);
    }

    void ShowFPS(int x,int y)
    {
        if (!IsReady)
            return;
        DrawFPS(x,y);
    }

    void Clear(int r, int g, int b)
    {
        if (!IsReady)
            return;
        mBackgroundColor.r = r;
        mBackgroundColor.g = g;
        mBackgroundColor.b = b;

        ClearBackground(mBackgroundColor);
    }

private:
    Graphics()
    {
        mDefaultFont = GetFontDefault();
        mTextSize = mDefaultFont.baseSize;

        mCamera.target.x = 0.0f;
        mCamera.target.y = 0.0f;

        mCamera.offset.y = 0.0f;
        mCamera.offset.x = 0.0f;

        mCamera.rotation = 0.0f;
        mCamera.zoom = 1.0f;

        mDefaultColor = {255, 255, 255, 255};
    }
    ~Graphics() {}

    Graphics(const Graphics &) = delete;
    Graphics &operator=(const Graphics &) = delete;

    Color mDefaultColor;
    Font mDefaultFont;
    int mSegments = 32;
    float mlineThickness = 1.0f;
    int mTextSize;
    Camera2D mCamera;
    Color mBackgroundColor = {0, 0, 0, 255};
};


static std::map<std::string, NativeFuncC> graphicsFunctions =
{

    {"circle(x:float,y:float,radius:float,isLine:bool)", [](VM *vm, ArgsView args) -> PyVar
    {
        float x = py_cast<float>(vm, args[0]);
        float y = py_cast<float>(vm, args[1]);
        float radius = py_cast<float>(vm, args[2]);
        bool isLine = py_cast<bool>(vm, args[3]);
        Graphics::Instance().Circle(x, y, radius, isLine);
        return py_var(vm, 0);
    }},

    {"rectangle(x:float,y:float,width:float,height:float,isLine:bool)", [](VM *vm, ArgsView args) -> PyVar
    {
        float x = py_cast<float>(vm, args[0]);
        float y = py_cast<float>(vm, args[1]);
        float width = py_cast<float>(vm, args[2]);
        float height = py_cast<float>(vm, args[3]);
        bool isLine = py_cast<bool>(vm, args[4]);
        Graphics::Instance().Rect(x, y, width, height, isLine);
        return py_var(vm, 0);
    }},

    {"ring(x:float,y:float,innerRadius:float,outerRadius:float,startAngle:float,endAngle:float,isLine:bool)", [](VM *vm, ArgsView args) -> PyVar
    {
        float x = py_cast<float>(vm, args[0]);
        float y = py_cast<float>(vm, args[1]);
        float innerRadius = py_cast<float>(vm, args[2]);
        float outerRadius = py_cast<float>(vm, args[3]);
        float startAngle = py_cast<float>(vm, args[4]);
        float endAngle = py_cast<float>(vm, args[5]);
        bool isLine = py_cast<bool>(vm, args[6]);
        Graphics::Instance().Ring(x, y, innerRadius, outerRadius, startAngle, endAngle, isLine);
        return py_var(vm, 0);
    }},

    {"line(x1:float,y1:float,x2:float,y2:float)", [](VM *vm, ArgsView args) -> PyVar
    {
        float x1 = py_cast<float>(vm, args[0]);
        float y1 = py_cast<float>(vm, args[1]);
        float x2 = py_cast<float>(vm, args[2]);
        float y2 = py_cast<float>(vm, args[3]);
        Graphics::Instance().Line(x1, y1, x2, y2);
        return py_var(vm, 0);
    }},

    {"drawScaleRotated(id:int,x:float,y:float,scale:float,rotation:float)", [](VM *vm, ArgsView args) -> PyVar
    {
        unsigned int id = py_cast<unsigned int>(vm, args[0]);
        float x = py_cast<float>(vm, args[1]);
        float y = py_cast<float>(vm, args[2]);
        float scale = py_cast<float>(vm, args[3]);
        float rotation = py_cast<float>(vm, args[4]);
        Graphics::Instance().Render(id, x, y, scale, rotation);
        return py_var(vm, 0);
    }},

    {"draw(id:int,x:float,y:float)", [](VM *vm, ArgsView args) -> PyVar
    {
        unsigned int id = py_cast<unsigned int>(vm, args[0]);
        float x = py_cast<float>(vm, args[1]);
        float y = py_cast<float>(vm, args[2]);
        
        Graphics::Instance().Render(id, x, y);
        return py_var(vm, 0);
    }},

    {"showFPS(x:int,y:int)", [](VM *vm, ArgsView args) -> PyVar
    {
        int x = py_cast<int>(vm, args[0]);
        int y = py_cast<int>(vm, args[1]);
        Graphics::Instance().ShowFPS(x, y);
        return py_var(vm, 0);
    }},


    {"setColor(r:int,g:int,b:int)", [](VM *vm, ArgsView args) -> PyVar
    {
        int r = py_cast<int>(vm, args[0]);
        int g = py_cast<int>(vm, args[1]);
        int b = py_cast<int>(vm, args[2]);
        Graphics::Instance().SetColor(r, g, b);
        return py_var(vm, 0);
    }},
     {"setTextSize(size:int)", [](VM *vm, ArgsView args) -> PyVar
    {
        int size = py_cast<int>(vm, args[0]);
        Graphics::Instance().SetTextSize(size);
        return py_var(vm, 0);
    }},
     {"text(x:int,y:int,text:str)", [](VM *vm, ArgsView args) -> PyVar
    {
        int x = py_cast<int>(vm, args[0]);
        int y = py_cast<int>(vm, args[1]);
        const  char* text = py_cast<const  char*>(vm, args[2]);
        Graphics::Instance().Text(x, y, text);
        return py_var(vm, 0);
    }},

    {"setAlpha(a:int)", [](VM *vm, ArgsView args) -> PyVar
    {
        int a = py_cast<int>(vm, args[0]);
        Graphics::Instance().SetAlpha(a);
        return py_var(vm, 0);
    }},


    {"clear(r:int,g:int,b:int)", [](VM *vm, ArgsView args) -> PyVar
    {
        int r = py_cast<int>(vm, args[0]);
        int g = py_cast<int>(vm, args[1]);
        int b = py_cast<int>(vm, args[2]);
        Graphics::Instance().Clear(r, g, b);
        return py_var(vm, 0);
    }},
     {"begin()", [](VM *vm, ArgsView args) -> PyVar
    {
        BeginDrawing();
        return py_var(vm, 0);
    }},
     {"end()", [](VM *vm, ArgsView args) -> PyVar
    {
        EndDrawing();
        return py_var(vm, 0);
    }},
     {"beginView()", [](VM *vm, ArgsView args) -> PyVar
    {
        Graphics::Instance().Begin();
        return py_var(vm, 0);
    }},
     {"endView()", [](VM *vm, ArgsView args) -> PyVar
    {
        Graphics::Instance().End();
        return py_var(vm, 0);
    }},
    {"setViewPosition(x:float,y:float)", [](VM *vm, ArgsView args) -> PyVar
    {
        float x = py_cast<float>(vm, args[0]);
        float y = py_cast<float>(vm, args[1]);
        Graphics::Instance().SetViewPosition(x, y);
        return py_var(vm, 0);
    }},

    {"setViewCenter(x:float,y:float)", [](VM *vm, ArgsView args) -> PyVar
    {
        float x = py_cast<float>(vm, args[0]);
        float y = py_cast<float>(vm, args[1]);
        Graphics::Instance().SetViewCenter(x, y);
        return py_var(vm, 0);
    }},

    {"setViewZoom(value:float)", [](VM *vm, ArgsView args) -> PyVar
    {
        float value = py_cast<float>(vm, args[0]);
        Graphics::Instance().SetViewZoom(value);
        return py_var(vm, 0);
    }},
    {"setViewRotation(value:float)", [](VM *vm, ArgsView args) -> PyVar
    {
        float value = py_cast<float>(vm, args[0]);
        Graphics::Instance().SetViewRotation(value);
        return py_var(vm, 0);
    }},








};

inline void RegisterGraphicsFunctions(VM* vm)
{
    PyObject* mod = vm->new_module("graphics");
   for (const auto& func : graphicsFunctions) 
   {
        vm->bind(mod, func.first.c_str(), func.second);
      
   }
}