del *.bak /s
del *.ddk /s
del *.edk /s
del *.lst /s
del *.lnp /s
del *.mpf /s
del *.mpj /s
del *.obj /s
del *.omf /s
::del *.opt /s  ::不允许删除JLINK的设置
del *.plg /s
del *.rpt /s
del *.tmp /s
del *.__i /s
del *.crf /s
del *.o /s
del *.d /s
del *.axf /s
del *.tra /s
del *.dep /s
del JLinkLog.txt /s
del *.scvd /s
del *.iex /s
del *.htm /s
del *.sct /s
del *.map /s
del *.hex /s
del *.mxproject /s
del *.Japker /s
for /f "delims=" %%i in ('dir /s/b/ad RTE*') do (
  rd /s/q "%%~i"
)
for /f "delims=" %%a in ('dir . /b /ad /s ^|sort /r' ) do rd /q "%%a" 2>nul
for /f "delims=" %%i in ('dir /s/b/ad .vscode*') do (
  rd /s/q "%%~i"
)
for /f "delims=" %%i in ('dir /s/b/ad DebugConfig*') do (
  rd /s/q "%%~i"
)
exit
