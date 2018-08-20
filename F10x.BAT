SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Rational\common;C:\Program Files\Calibre2\;C:\Program Files\Microsoft VS Code\bin;C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=F10x
SET CPU_CLOCK=0x007A1200
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_stm32f10x_md._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\core_cm3.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\system_stm32f10x.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_usart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lyzkgpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lyzkusart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\LyzkLibrary_stm32F10x.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\LyzkLibrary_stm32F10x.axf" --i32combined --output ".\Objects\LyzkLibrary_stm32F10x.hex"
