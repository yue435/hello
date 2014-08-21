hello
=====

have a try
#include "mcu_def.h"

void delayMs(unsigned int ms)//较精确的毫秒级延时
{
  volatile unsigned int i;
  for (i=0;i<ms;i++)
    __delay_cycles((MCU_SPEED * 1000));
}


(http://github.com/yue435/hello/raw/master/image/mmc.jpg)


