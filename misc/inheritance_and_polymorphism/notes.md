https://tinylab.org/generate-clean-assembly/

-fno-stack-protector：去掉 stack 保护，stack protector 用于检查 stack 是否被踩
-fomit-frame-pointer：不用 fp 寄存器 rbp/ebp，直接用 stack 寄存器 rsp/esp 就好了
-fno-asynchronous-unwind-tables：消除 .eh_frame section

虚继承:
https://www.cnblogs.com/ThousandPine/p/18111381