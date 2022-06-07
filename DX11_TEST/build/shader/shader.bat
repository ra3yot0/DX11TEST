@echo on
"C:\Program Files (x86)\Windows Kits\10\bin\10.0.22000.0\x64\fxc.exe" ^
/T vs_5_0 /E vs_main /Fh ../../include/shader/vshader.h ../../src/shader/shader.vsh
"C:\Program Files (x86)\Windows Kits\10\bin\10.0.22000.0\x64\fxc.exe" ^
/T ps_5_0 /E ps_main /Fh ../../include/shader/pshader.h ../../src/shader/shader.psh 