#include "EEPROM.h"

void EEPROM_Init(void)
{
    uint32_t ui32EEPROMInit;
//    uint32_t pui32Data = 'Y';
//    uint32_t pui32Read;

    //ʹ��EEPROMʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0))
    {
    }

    //�ȴ�EEPROM��ʼ�����
    ui32EEPROMInit = EEPROMInit();
    if(ui32EEPROMInit != EEPROM_INIT_OK)
    {
        while(1)
        {
        }
    }


//    //��EEPROM��д���ʵ�ֵ
//    EEPROMProgram(&pui32Data, 0x400, sizeof(pui32Data));
//    //��ȡEERPOM�е�ֵ
//    EEPROMRead(&pui32Read, 0x400, sizeof(pui32Read));
//    UARTprintf("pui32Read = %d\n",pui32Read);
}
