#pragma once
//Add if deff for windows platform

#ifdef ENGINE_BUILD_DLL
    #define ENGINE_API __declspec(dllexport)
#else
    #define ENGINE_API __declspec(dllimport)
#endif
