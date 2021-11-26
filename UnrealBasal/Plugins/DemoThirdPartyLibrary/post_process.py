import os
import shutil
from pathlib import Path

RootDir = os.path.dirname(__file__)
print("RootDir: ", RootDir)

RootDir = Path(RootDir)

ThirdLibFrom = RootDir / "Source/ThirdParty/MyExampleThirdParty/x64/Release/ExampleLibrary.dll"
ThirdLibCopy2 = RootDir / "Binaries/ThirdParty/MyExampleThirdParty/Win64/ExampleLibrary.dll"

ThirdLibCopy2Dir = os.path.dirname(ThirdLibCopy2)
if not os.path.exists(ThirdLibCopy2Dir):
	os.makedirs(os.path.dirname(ThirdLibCopy2))

if not os.path.exists(ThirdLibCopy2):
    os.remove(ThirdLibCopy2)

shutil.copyfile(ThirdLibFrom, ThirdLibCopy2)
