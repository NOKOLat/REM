import os

print("befAction")

os.chdir(os.path.dirname(os.path.abspath(__file__)))
if os.path.exists("./../Core/Src/main.cpp"):
	os.rename("./../Core/Src/main.cpp", "./../Core/Src/main.c")
if os.path.exists("./../Core/Src/stm32c0xx_it.cpp"):
	os.rename("./../Core/Src/stm32c0xx_it.cpp", "./../Core/Src/stm32c0xx_it.c")
