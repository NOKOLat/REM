#!/bin/bash

cd `dirname $0`
cd ../Core/Src

mv main.c main.cpp
mv stm32c0xx_it.c stm32c0xx_it.cpp
