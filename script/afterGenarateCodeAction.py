#!/usr/bin/python3
import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))
if os.path.exists("./../Core/Src/main.c"):
	os.rename("./../Core/Src/main.c", "./../Core/Src/main.cpp")
if os.path.exists("./../Core/Src/stm32c0xx_it.c"):
	os.rename("./../Core/Src/stm32c0xx_it.c", "./../Core/Src/stm32c0xx_it.cpp")