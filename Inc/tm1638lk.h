// SPDX-FileCopyrightText: 2026 Alexander Zvolinskiy <aezv.global@gmail.com>
// SPDX-License-Identifier: MIT

/**
 * @file    tm1638lk.h
 * @brief   Заголовочный файл библиотеки для работы с модулем TM1638 led&key
 */

#ifndef TM1638LK_H
#define TM1638LK_H

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TM1638LK_WRITE_AUTOINCREMENT_ADDR  0x40
#define TM1638LK_WRITE_FIXED_ADDR          0x44
#define TM1638LK_WRITE_ADDR0               0xC0

#define TM1638LK_READ                      0x42

#define TM1638LK_DIGIT_0 0x3F
#define TM1638LK_DIGIT_1 0x06
#define TM1638LK_DIGIT_2 0x5B
#define TM1638LK_DIGIT_3 0x4F
#define TM1638LK_DIGIT_4 0x66
#define TM1638LK_DIGIT_5 0x6D
#define TM1638LK_DIGIT_6 0x7D
#define TM1638LK_DIGIT_7 0x07
#define TM1638LK_DIGIT_8 0x7F
#define TM1638LK_DIGIT_9 0x6F

typedef struct {
    SPI_HandleTypeDef *spi;
    GPIO_TypeDef *stb_port;
    uint16_t stb_pin;
} TM1638LK_HandleTypeDef;

/**
 * @brief Инициализация модуля TM1638LK
 * @param handle: указатель на структуру с настройками
 * @retval HAL_StatusTypeDef (HAL_OK / HAL_ERROR)
 */
HAL_StatusTypeDef TM1638LK_Init(TM1638LK_HandleTypeDef *handle);

/**
 * @brief Очистка регистров модуля TM1638LK
 * @param handle: указатель на структуру с настройками
 * @retval HAL_StatusTypeDef (HAL_OK / HAL_ERROR)
 */
HAL_StatusTypeDef TM1638LK_Clear(TM1638LK_HandleTypeDef *handle);

/**
 * @brief Очистка регистров светодиодов модуля TM1638LK
 * @param handle: указатель на структуру с настройками
 * @retval HAL_StatusTypeDef (HAL_OK / HAL_ERROR)
 */
HAL_StatusTypeDef TM1638LK_ClearLeds(TM1638LK_HandleTypeDef *handle);

/**
 * @brief Очистка регистров цифр модуля TM1638LK
 * @param handle: указатель на структуру с настройками
 * @retval HAL_StatusTypeDef (HAL_OK / HAL_ERROR)
 */
HAL_StatusTypeDef TM1638LK_ClearIndicators(TM1638LK_HandleTypeDef *handle);

/**
 * @brief Установка яркости модуля TM1638LK
 * @param handle: указатель на структуру с настройками
 * @param br: состояние отображения, 0 - выключено, 1 - включено
 * @param br: яркость, от 0 до 7
 * @retval HAL_StatusTypeDef (HAL_OK / HAL_ERROR)
 */
HAL_StatusTypeDef TM1638LK_SetBrightness(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t br);

/**
 * @brief Включение светодиода модуля TM1638LK
 * @param handle: указатель на структуру с настройками
 * @param state: состояние светодиода, 0 - выключен, 1 - включен
 * @param num: номер светодиода, от 0 до 7
 * @retval HAL_StatusTypeDef (HAL_OK / HAL_ERROR)
 */
HAL_StatusTypeDef TM1638LK_SetLed(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t num);

/**
 * @brief Включение цифры на индикаторе модуля TM1638LK
 * @param handle: указатель на структуру с настройками
 * @param state: состояние индикатора, 0 - выключен, 1 - включен
 * @param num: номер индикатора, от 0 до 7
 * @param digit: значение цифры, от 0 до 9
 * @param stateDot: состояние точки, 0 - выключена, 1 - включена
 * @retval HAL_StatusTypeDef (HAL_OK / HAL_ERROR)
 */
HAL_StatusTypeDef TM1638LK_SetDigit(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t num, uint8_t digit, uint8_t stateDot);

/**
 * @brief Включение символа английского алфавита на индикаторе модуля TM1638LK
 * @param handle: указатель на структуру с настройками
 * @param state: состояние индикатора, 0 - выключен, 1 - включен
 * @param num: номер индикатора, от 0 до 7
 * @param sym: значение символа
 * @param stateDot: состояние точки, 0 - выключена, 1 - включена
 * @retval HAL_StatusTypeDef (HAL_OK / HAL_ERROR)
 */
//HAL_StatusTypeDef TM1638LK_SetSymbolEn(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t num, char sym, uint8_t stateDot);

/**
 * @brief Включение символа русского алфавита на индикаторе модуля TM1638LK
 * @param handle: указатель на структуру с настройками
 * @param state: состояние индикатора, 0 - выключен, 1 - включен
 * @param num: номер индикатора, от 0 до 7
 * @param sym: значение символа
 * @param stateDot: состояние точки, 0 - выключена, 1 - включена
 * @retval HAL_StatusTypeDef (HAL_OK / HAL_ERROR)
 */
//HAL_StatusTypeDef TM1638LK_SetSymbolRu(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t num, char sym, uint8_t stateDot);

/**
 * @brief Считывание нажатия кнопок модуля TM1638LK
 * @param handle: указатель на структуру с настройками
 * @param keys: указатель на байт с значениями кнопок
 * @retval HAL_StatusTypeDef (HAL_OK / HAL_ERROR)
 */
HAL_StatusTypeDef TM1638LK_GetKeys(TM1638LK_HandleTypeDef *handle, uint8_t* keys);

#ifdef __cplusplus
}
#endif

#endif
