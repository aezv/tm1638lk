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

## Описание функций

#### HAL_StatusTypeDef TM1638LK_Init(TM1638LK_HandleTypeDef *handle)
Описание: инициализирует модуль
Параметры:  `TM1638LK_HandleTypeDef *handle` - указатель на структуру с настройками SPI
Возвращаемое значение: `HAL_StatusTypeDef` с значением `HAL_OK` или `HAL_ERROR`

#### HAL_StatusTypeDef TM1638LK_Clear(TM1638LK_HandleTypeDef *handle)
Описание: очищает все регистры
Параметры:  `TM1638LK_HandleTypeDef *handle` - указатель на структуру с настройками SPI
Возвращаемое значение: `HAL_StatusTypeDef` с значением `HAL_OK` или `HAL_ERROR`

#### HAL_StatusTypeDef TM1638LK_ClearLeds(TM1638LK_HandleTypeDef *handle)
Описание: очищает регистры светодиодов
Параметры:  `TM1638LK_HandleTypeDef *handle` - указатель на структуру с настройками SPI
Возвращаемое значение: `HAL_StatusTypeDef` с значением `HAL_OK` или `HAL_ERROR`

#### HAL_StatusTypeDef TM1638LK_ClearIndicators(TM1638LK_HandleTypeDef *handle)
Описание: очищает регистры семисегментных индикаторов
Параметры:  `TM1638LK_HandleTypeDef *handle` - указатель на структуру с настройками SPI
Возвращаемое значение: `HAL_StatusTypeDef` с значением `HAL_OK` или `HAL_ERROR`

#### HAL_StatusTypeDef TM1638LK_SetBrightness(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t br)
Описание: включает светодиоды и индикаторы, устанавливает их яркость 
Параметры:  `TM1638LK_HandleTypeDef *handle` - указатель на структуру с настройками SPI
            `uint8_t state` - состояние элементов: 0 - выключены, 1 - включены
            `uint8_t br` - уровень яркости элементов, от 0 до 7
Возвращаемое значение: `HAL_StatusTypeDef` с значением `HAL_OK` или `HAL_ERROR`

#### HAL_StatusTypeDef TM1638LK_SetLed(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t num)
Описание: включает/отключает выбранный светодиод (записывает/удаляет значение регистра)
Параметры:  `TM1638LK_HandleTypeDef *handle` - указатель на структуру с настройками SPI
            `uint8_t state` - состояние светодиода: 0 - выключен, 1 - включен
            `uint8_t num` - номер светодиода, от 0 до 7
Возвращаемое значение: `HAL_StatusTypeDef` с значением `HAL_OK` или `HAL_ERROR`

#### HAL_StatusTypeDef TM1638LK_SetDigit(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t num, uint8_t digit, uint8_t stateDot)
Описание: включает/отключает выбранный семисегментный индикатор, выводит на него цифру (записывает/удаляет значение регистра)
Параметры:  `TM1638LK_HandleTypeDef *handle` - указатель на структуру с настройками SPI
            `uint8_t state` - состояние индикатора: 0 - выключен, 1 - включен
            `uint8_t num` - номер индикатора, от 0 до 7
            `uint8_t digit` - значение цифры, выводимой на индикатор, от 0 до 9
            `uint8_t stateDot` - состояние точки индикатора, 0 - выключена, 1 - включена
Возвращаемое значение: `HAL_StatusTypeDef` с значением `HAL_OK` или `HAL_ERROR`

#### HAL_StatusTypeDef TM1638LK_GetKeys(TM1638LK_HandleTypeDef *handle, uint8_t* keys)
Описание: считывает нажатия кнопок (считывает значения регистров)
Параметры:  `TM1638LK_HandleTypeDef *handle` - указатель на структуру с настройками SPI
            `uint8_t* keys` - указатель на переменную типа `uint8_t`, записывает в нее текущее состояние кнопок,
                            где младший бит - состояние первой кнопки, а старший бит - состояние последней кнопки.
Возвращаемое значение: `HAL_StatusTypeDef` с значением `HAL_OK` или `HAL_ERROR`


