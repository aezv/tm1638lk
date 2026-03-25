# TM1638LED&KEY STM32 HAL Library
Библиотека для работы с модулем TM1638 LED&KEY на STM32 HAL

## Фото и схема модуля
![](https://github.com/aezv/tm1638lk/blob/main/docs/tm1638_ledkey.png)
![](https://github.com/aezv/tm1638lk/blob/main/docs/tm1638_ledkey_sch.png)

## Настройка SPI в CubeMX
Настройка полудуплексного SPI:

    Mode: Half-Duplex Master
    Hardware NSS Signal: Disable

    Frame Format: Motorola
    Data Size: 8 Bits
    First Bit: LSB First

    Prescaler (for Baud Rate): [Baud Rate не должен превышать 1000 KBits/s]
    Clock Polarity (CPOL): High
    Clock Phase (CPHA): 2 Edge

    CRC Calculation: Disabled
    NSS Signal Type: Software

Активировать пин SPI_STB (Chip Select) как GPIO_Output:

    GPIO output level: Low
    GPIO mode: Output Push Pull
    GPIO Pull-up/Pull-down: No pull-up and no pull-down
    Maximum output speed: Medium

## Использование
Объявляем структуру и заполняем ее данными:
```
TM1638LK_HandleTypeDef ledkey;
ledkey.spi = &hspi1;
ledkey.stb_port = SPI1_STB_GPIO_Port;
ledkey.stb_pin = SPI1_STB_Pin;
```
Инициализируем модуль и включаем его:
```
TM1638LK_Init(&ledkey);
TM1638LK_SetBrightness(&ledkey, 1, 5);
```
Зажигаем все светодиоды и индикаторы:
```
for(uint8_t i = 0; i < 8; i++)
{
    TM1638LK_SetLed(&ledkey, 1, i);
    TM1638LK_SetDigit(&ledkey, 1, i, i, 1);
}
```
