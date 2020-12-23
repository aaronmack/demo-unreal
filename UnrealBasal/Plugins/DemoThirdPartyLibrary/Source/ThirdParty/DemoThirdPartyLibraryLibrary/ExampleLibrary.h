#if defined _WIN32 || defined _WIN64
#define EXAMPLELIBRARY_IMPORT __declspec(dllimport)
#elif defined __linux__
#define EXAMPLELIBRARY_IMPORT __attribute__((visibility("default")))
#else
#define EXAMPLELIBRARY_IMPORT
#endif

#define DllExport   __declspec( dllexport )


EXAMPLELIBRARY_IMPORT void ExampleLibraryFunction();
EXAMPLELIBRARY_IMPORT void ExampleLibraryFunction1();
EXAMPLELIBRARY_IMPORT int ExampleLibraryFunction2();