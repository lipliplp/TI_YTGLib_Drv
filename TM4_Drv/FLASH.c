#include "FLASH.h"

//FLASH模块初始化
void FLASH_Init(void)
{
    uint32_t pui32Data = 'y';

    //擦除1KB的FLASH 选择大于0x17e6，并且在1k的整数倍的地址
    FlashErase(0x10000);

    //写入FLASH
    FlashProgram(&pui32Data, 0x10000, sizeof(pui32Data));

    //打印
    UARTprintf("写入成功");
}
