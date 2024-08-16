#!/bin/bash

cd `dirname $0`
cd ../Core/Src

mv main.cpp main.c
mv stm32c0xx_it.cpp stm32c0xx_it.c
