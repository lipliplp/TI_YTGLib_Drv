#include "FLASH.h"

//FLASHģ���ʼ��
void FLASH_Init(void)
{
    uint32_t pui32Data = 'y';

    //����1KB��FLASH ѡ�����0x17e6��������1k���������ĵ�ַ
    FlashErase(0x10000);

    //д��FLASH
    FlashProgram(&pui32Data, 0x10000, sizeof(pui32Data));

    //��ӡ
    UARTprintf("д��ɹ�");
}
