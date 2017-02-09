@echo off
cls

del GradeCalcDriver.o
g++ -c GradeCalcDriver.cpp

g++ -o Final_Grade_Needed_Calc.exe GradeCalcDriver.o

Final_Grade_Needed_Calc.exe