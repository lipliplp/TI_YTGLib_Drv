### 📕TI常见模块通用库

为了准备电赛所写的MSP430以及TM4的通用内设库（目前尚未完善）

#### ①🔨模块库使用方法

引入**TI_YTGLib_Drv**文件夹放入工程文件中（❗注：引入到工程的最外层文件里，即工程根目录中）

> git submodule add https://github.com/name-longming/TI_YTGLib_Drv 

#### ②🌅MSP430模块库内容

- [x] 时钟频率设置
- [x] 精准毫秒，微秒延时
- [x] LED灯控制
- [x] 外部中断控制
- [x] 按键扫描
- [x] 定时器中断
- [x] PWM波生成
- [x] 串口通信
- [x] ADC / DAC采集
- [ ] 陀螺仪控制与解算
- [x] OLED驱动

### ③🌅TM4模块库内容

- [x] 时钟频率设置
- [x] 精准毫秒，微秒延时
- [x] LED灯控制
- [x] 外部中断控制
- [x] 按键扫描
- [x] 定时器中断
- [x] PWM波生成
- [x] 串口通信
- [x] ADC / DAC采集
- [x] QEI编码器
- [x] EEPROM
- [x] FLASH