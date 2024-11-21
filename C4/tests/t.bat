@echo off
copy %1 cooling.in > nul
d
copy cooling.out %1.a > nul
check cooling.in cooling.out %1.a
