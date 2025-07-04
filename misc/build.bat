@echo off

mkdir build
pushd build
cl /Zi W:\Handmade\code\HandmadeWorked.cpp user32.lib gdi32.lib 
popd