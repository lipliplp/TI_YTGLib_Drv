#include "EEPROM.h"

void EEPROM_Init(void)
{
    uint32_t ui32EEPROMInit;
//    uint32_t pui32Data = 'Y';
//    uint32_t pui32Read;

    //使能EEPROM时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0))
    {
    }

    //等待EEPROM初始化完成
    ui32EEPROMInit = EEPROMInit();
    if(ui32EEPROMInit != EEPROM_INIT_OK)
    {
        while(1)
        {
        }
    }


//    //向EEPROM中写入适当值
//    EEPROMProgram(&pui32Data, 0x400, sizeof(pui32Data));
//    //读取EERPOM中的值
//    EEPROMRead(&pui32Read, 0x400, sizeof(pui32Read));
//    UARTprintf("pui32Read = %d\n",pui32Read);
}
