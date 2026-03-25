#include "tm1638lk.h"

static void TM1638LK_Select(TM1638LK_HandleTypeDef *handle)
{
    HAL_GPIO_WritePin(handle->stb_port, handle->stb_pin, GPIO_PIN_RESET);
}
static void TM1638LK_Unselect(TM1638LK_HandleTypeDef *handle)
{
    HAL_GPIO_WritePin(handle->stb_port, handle->stb_pin, GPIO_PIN_SET);
}
static HAL_StatusTypeDef TM1638LK_SendByte(TM1638LK_HandleTypeDef *handle, uint8_t data)
{
    return HAL_SPI_Transmit(handle->spi, &data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef TM1638LK_Init(TM1638LK_HandleTypeDef *handle)
{
    if (handle == NULL || handle->spi == NULL || handle->stb_port == NULL) {
        return HAL_ERROR;
    }
    HAL_StatusTypeDef status = TM1638LK_SetBrightness(handle, 0, 0);
    if(status != HAL_OK) return status;
    return TM1638LK_Clear(handle);
}

HAL_StatusTypeDef TM1638LK_Clear(TM1638LK_HandleTypeDef *handle)
{
    if (handle == NULL || handle->spi == NULL || handle->stb_port == NULL) {
        return HAL_ERROR;
    }

    TM1638LK_Select(handle);
    HAL_StatusTypeDef status = TM1638LK_SendByte(handle, TM1638LK_WRITE_AUTOINCREMENT_ADDR);
    TM1638LK_Unselect(handle);
    if(status != HAL_OK) return status;
    HAL_Delay(1);

    TM1638LK_Select(handle);
    status = TM1638LK_SendByte(handle, TM1638LK_WRITE_ADDR0);
    if(status != HAL_OK) return status;

    for(uint8_t i = 0; i < 16; i++)
    {
        status = TM1638LK_SendByte(handle, 0x00);
        if(status != HAL_OK) return status;
    }
    TM1638LK_Unselect(handle);
    HAL_Delay(1);
    return status;
}
HAL_StatusTypeDef TM1638LK_ClearLeds(TM1638LK_HandleTypeDef *handle)
{
    if (handle == NULL || handle->spi == NULL || handle->stb_port == NULL) {
        return HAL_ERROR;
    }

    TM1638LK_Select(handle);
    HAL_StatusTypeDef status = TM1638LK_SendByte(handle, TM1638LK_WRITE_FIXED_ADDR);
    TM1638LK_Unselect(handle);
    if(status != HAL_OK) return status;
    HAL_Delay(1);

    for(uint8_t i = 0; i < 8; i++)
    {
        uint8_t cmd = 0xC1 + (i * 2);
        TM1638LK_Select(handle);
        status = TM1638LK_SendByte(handle, cmd);
        if(status != HAL_OK) return status;
        status = TM1638LK_SendByte(handle, 0x00);
        if(status != HAL_OK) return status;
        TM1638LK_Unselect(handle);
        HAL_Delay(1);
    }
    return status;
}
HAL_StatusTypeDef TM1638LK_ClearIndicators(TM1638LK_HandleTypeDef *handle)
{
    if (handle == NULL || handle->spi == NULL || handle->stb_port == NULL) {
        return HAL_ERROR;
    }

    TM1638LK_Select(handle);
    HAL_StatusTypeDef status = TM1638LK_SendByte(handle, TM1638LK_WRITE_FIXED_ADDR);
    TM1638LK_Unselect(handle);
    if(status != HAL_OK) return status;
    HAL_Delay(1);

    for(uint8_t i = 0; i < 8; i++)
    {
        uint8_t cmd = 0xC0 + (i * 2);
        TM1638LK_Select(handle);
        status = TM1638LK_SendByte(handle, cmd);
        if(status != HAL_OK) return status;
        status = TM1638LK_SendByte(handle, 0x00);
        if(status != HAL_OK) return status;
        TM1638LK_Unselect(handle);
        HAL_Delay(1);
    }
    return status;
}

HAL_StatusTypeDef TM1638LK_SetBrightness(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t br)
{
    if (handle == NULL || handle->spi == NULL || handle->stb_port == NULL) {
        return HAL_ERROR;
    }

    if (state > 1) state = 1;
    if (br > 7) br = 7;

    uint8_t cmd = 0x80 | (state << 3) | br;

    TM1638LK_Select(handle);
    HAL_StatusTypeDef status = TM1638LK_SendByte(handle, cmd);
    TM1638LK_Unselect(handle);
    if(status != HAL_OK) return status;
    HAL_Delay(1);
    return status;
}

HAL_StatusTypeDef TM1638LK_SetLed(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t num)
{
    if (handle == NULL || handle->spi == NULL || handle->stb_port == NULL) {
        return HAL_ERROR;
    }

    if(state > 1) state = 1;
    if(num > 7) num = 7;

    TM1638LK_Select(handle);
    HAL_StatusTypeDef status = TM1638LK_SendByte(handle, TM1638LK_WRITE_FIXED_ADDR);
    TM1638LK_Unselect(handle);
    if(status != HAL_OK) return status;
    HAL_Delay(1);

    uint8_t cmd = 0xC1 + (num * 2);
    TM1638LK_Select(handle);
    status = TM1638LK_SendByte(handle, cmd);
    if(status != HAL_OK) return status;

    status = TM1638LK_SendByte(handle, state);
    if(status != HAL_OK) return status;
    TM1638LK_Unselect(handle);
    HAL_Delay(1);
    return status;
}

HAL_StatusTypeDef TM1638LK_SetDigit(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t num, uint8_t digit, uint8_t stateDot)
{
    if (handle == NULL || handle->spi == NULL || handle->stb_port == NULL) {
        return HAL_ERROR;
    }

    if(state > 1) state = 1;
    if(num > 7) num = 7;
    if(digit > 9) digit = 9;
    if(stateDot > 1) stateDot = 1;

    TM1638LK_Select(handle);
    HAL_StatusTypeDef status = TM1638LK_SendByte(handle, TM1638LK_WRITE_FIXED_ADDR);
    TM1638LK_Unselect(handle);
    if(status != HAL_OK) return status;
    HAL_Delay(1);

    uint8_t cmd = 0xC0 + (num * 2);
    TM1638LK_Select(handle);
    status = TM1638LK_SendByte(handle, cmd);
    if(status != HAL_OK) return status;

    if(state)
    {
        switch (digit)
        {
        case 0:
            cmd = TM1638LK_DIGIT_0;
            break;
        case 1:
            cmd = TM1638LK_DIGIT_1;
            break;
        case 2:
            cmd = TM1638LK_DIGIT_2;
            break;
        case 3:
            cmd = TM1638LK_DIGIT_3;
            break;
        case 4:
            cmd = TM1638LK_DIGIT_4;
            break;
        case 5:
            cmd = TM1638LK_DIGIT_5;
            break;
        case 6:
            cmd = TM1638LK_DIGIT_6;
            break;
        case 7:
            cmd = TM1638LK_DIGIT_7;
            break;
        case 8:
            cmd = TM1638LK_DIGIT_8;
            break;
        case 9:
            cmd = TM1638LK_DIGIT_9;
            break;
        default:
            status = HAL_ERROR;
        }
        if(stateDot)
            cmd = cmd | 0x80;
        status = TM1638LK_SendByte(handle, cmd);
        if(status != HAL_OK) return status;
    }
    else
    {
        status = TM1638LK_SendByte(handle, state);
        if(status != HAL_OK) return status;
    }
    TM1638LK_Unselect(handle);
    HAL_Delay(1);
    return status;
}

//HAL_StatusTypeDef TM1638LK_SetSymbolEn(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t num, char sym, uint8_t stateDot)
//{
//
//}
//
//HAL_StatusTypeDef TM1638LK_SetSymbolRu(TM1638LK_HandleTypeDef *handle, uint8_t state, uint8_t num, char sym, uint8_t stateDot)
//{
//
//}

HAL_StatusTypeDef TM1638LK_GetKeys(TM1638LK_HandleTypeDef *handle, uint8_t* keys)
{
    if (handle == NULL || handle->spi == NULL || handle->stb_port == NULL) {
        return HAL_ERROR;
    }

    TM1638LK_Select(handle);
    HAL_StatusTypeDef status = TM1638LK_SendByte(handle, TM1638LK_READ);
    if (status != HAL_OK) return status;
    uint8_t keys_raw[4];
    status = HAL_SPI_Receive(handle->spi, keys_raw, 4, HAL_MAX_DELAY);
    TM1638LK_Unselect(handle);
    if (status != HAL_OK) return status;
    HAL_Delay(1);

    uint32_t keys_data =
    (uint32_t)keys_raw[0] |
    ((uint32_t)keys_raw[1] << 8) |
    ((uint32_t)keys_raw[2] << 16) |
    ((uint32_t)keys_raw[3] << 24);

    *keys = 0x00;
    *keys |= (keys_data & 0x00000001) ? 0x01 : 0x00;
    *keys |= (keys_data & 0x00000100) ? 0x02 : 0x00;
    *keys |= (keys_data & 0x00010000) ? 0x04 : 0x00;
    *keys |= (keys_data & 0x01000000) ? 0x08 : 0x00;
    *keys |= (keys_data & 0x00000010) ? 0x10 : 0x00;
    *keys |= (keys_data & 0x00001000) ? 0x20 : 0x00;
    *keys |= (keys_data & 0x00100000) ? 0x40 : 0x00;
    *keys |= (keys_data & 0x10000000) ? 0x80 : 0x00;

    return status;
}
