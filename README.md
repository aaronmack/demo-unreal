# Demo Unreal

## Preparation

* HoudiniEngine.V2
  * https://github.com/sideeffects/HoudiniEngineForUnreal-v2

## Examples

* unreal_basal
  * Actor classes


# Houdini

## HDK

### Examples Compiled

```bash
# set path=C:\Program Files\Side Effects Software\Houdini 18.5.351 Python3\bin;%path%
cd C:\DEV_PROJECT\dev-repository\demo-unreal\houdini_delve\hdk_examples\build
cmake ..
cmake --build . --config Release -- /M:8
```

## Resources

```bash
# Generated by hcustom --output_makevars
WIN32_KIT = C:/Windows Kits/10
WIN32_KIT_VERSION = 10.0.18362.0
CC = "$(MSVCDir)/bin$(AMD64_SUFFIX)/cl" -c
LINK = "$(MSVCDir)/bin$(AMD64_SUFFIX)/link"
EMBED_MANIFEST = 0
HDEFINES = $(ARCHDEFS) -DI386 -DWIN32 -DSWAP_BITFIELDS -D_WIN32_WINNT=0x0600 -DNOMINMAX -DSTRICT -DWIN32_LEAN_AND_MEAN -D_USE_MATH_DEFINES -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS -DSESI_LITTLE_ENDIAN -DHBOOST_ALL_NO_LIB -DEIGEN_MALLOC_ALREADY_ALIGNED=0 -DFBX_ENABLED=1 -DOPENCL_ENABLED=1 -DOPENVDB_ENABLED=1
INCINC = -I . $(INCDIRS) -I "$(HFS)/toolkit/include" -I "$(MSVCDir)/include" -I "$(WIN32_KIT)/Include/$(WIN32_KIT_VERSION)/ucrt" -I "$(WIN32_KIT)/Include/$(WIN32_KIT_VERSION)/um" -I "$(WIN32_KIT)/Include/$(WIN32_KIT_VERSION)/shared"
WFLAGS = -wd4355 -w14996
OPTIMIZER = -O2 -DNDEBUG -MD -EHsc -GR -bigobj
HLIBINC = -LIBPATH:"$(HFS)/custom/houdini/dsolib"
HLIBS = "$(HFS)/custom/houdini/dsolib/*.a" "$(HFS)/custom/houdini/dsolib/*.lib"
LIB_ARCH_SUFFIX = /x64
SYSLIBINC = -LIBPATH:"$(MSVCDir)/lib$(LIB_ARCH_SUFFIX)" -LIBPATH:"$(WIN32_KIT)/Lib/$(WIN32_KIT_VERSION)/ucrt$(LIB_ARCH_SUFFIX)" -LIBPATH:"$(WIN32_KIT)/Lib/$(WIN32_KIT_VERSION)/um$(LIB_ARCH_SUFFIX)"
SHAREDFLAG = -DLL
OBJOUTPUT = -Fo
DSOOUTPUT = -out:
SAOUTPUT = -out:
CXXFLAGS = -nologo -TP -Zc:forScope -Zc:rvalueCast -Zc:inline -Zc:strictStrings -std:c++14 -Zc:referenceBinding -Zc:ternary -Zc:throwingNew -permissive- -Zc:__cplusplus
OBJFLAGS = $(HDEFINES) $(INCINC) $(WFLAGS) $(OPTIMIZER) $(HCUSTOM_CFLAGS)
DSOFLAGS = $(SYSLIBINC) $(LIBDIRS) $(LIBS) $(SYSLIBS) $(HLIBINC) $(HLIBS) $(HCUSTOM_LDFLAGS)
SAFLAGS = $(DSOFLAGS)
```

# Blender

* Wiki: `https://wiki.blender.org/wiki/Building_Blender`
* Wiki Archive: `https://archive.blender.org/wiki/index.php/`
* Github Source Code: `https://github.com/blender/blender.git`
