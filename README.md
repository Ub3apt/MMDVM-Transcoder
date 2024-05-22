This is the source code of the MMDVM-Transcoder firmware that supports transcoding to and from the following digital and analogue audio modes:
- D-Star
- DMR
- YSF (DN and VW mode)
- P25 phase 1 (with or without FEC)
- NXDN
- M17
- PCM

The available conversions depends on the hardware available. With no AMBE DSP chip then very limited transcoding is possible, but with a DVSI AMBE3000 all conversions are possible.

It runs on the the ST-Micro or STM32F722 or STM32H723 processor and a custom AMBE board. The design of this board will be made available once it's design has been finalised.

In addition there are two supplied programs that exercise the transcoder. Tester is used to test the basic funationality of the transcoder and to hopefully enable the finding of serious bugs that may be added during development. FileConvert is used to convert the contents of DV and WAV files to and from different modes, it is similar in functionality to the older AMBETools in this GitHub repository.

This software is licenced under the GPL v2 and is primarily intended for amateur and educational use.
----------------------------
Это исходный код прошивки MMDVM-Transcoder, которая поддерживает перекодирование в следующие цифровые и аналоговые аудиорежимы и обратно:

D-Стар
ДМР
YSF (режим DN и VW)
P25 фаза 1 (с FEC или без него)
НКСДН
М17
ПКМ
Доступные преобразования зависят от доступного оборудования. Без чипа AMBE DSP возможно очень ограниченное транскодирование, но с DVSI AMBE3000 возможны все преобразования.

Он работает на процессоре ST-Micro, STM32F722 или STM32H723 и специальной плате AMBE. Дизайн этой доски будет доступен после завершения ее разработки.

Кроме того, в комплект поставки входят две программы, которые используют транскодер. Тестер используется для проверки основных функций транскодера и, возможно, для обнаружения серьезных ошибок, которые могут быть добавлены во время разработки. FileConvert используется для преобразования содержимого файлов DV и WAV в разные режимы и из них. По функциональности он аналогичен более старым AMBETools в этом репозитории GitHub.

Это программное обеспечение распространяется по лицензии GPL v2 и предназначено в первую очередь для любительского и образовательного использования.
