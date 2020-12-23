#if defined _WIN32 || defined _WIN64
    #include <Windows.h>

    #define EXAMPLELIBRARY_EXPORT __declspec(dllexport)
#else
    #include <stdio.h>
#endif

#ifndef EXAMPLELIBRARY_EXPORT
    #define EXAMPLELIBRARY_EXPORT
#endif

EXAMPLELIBRARY_EXPORT void ExampleLibraryFunction()
{
#if defined _WIN32 || defined _WIN64
	MessageBox(NULL, TEXT("Keep Going."), TEXT("Third World"), MB_OK);
#else
    printf("Loaded ExampleLibrary from Third Party Plugin sample");
#endif
}

EXAMPLELIBRARY_EXPORT void ExampleLibraryFunction1()
{
#if defined _WIN32 || defined _WIN64
	MessageBox(NULL, TEXT("Don't give up."), TEXT("Seventh world"), MB_OK);
#else
	printf("Loaded ExampleLibrary from Third Party Plugin sample");
#endif
}

EXAMPLELIBRARY_EXPORT int ExampleLibraryFunction2()
{
#if defined _WIN32 || defined _WIN64
	MessageBox(NULL, TEXT("There are three things I only believed in the world, Knowledge, Love and You."), TEXT("Tenth world"), MB_OK);
#else
	printf("Loaded ExampleLibrary from Third Party Plugin sample");
#endif
	return 1;
}