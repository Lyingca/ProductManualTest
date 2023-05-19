//
// Created by 陈骏骏 on 2023/5/4.
//

#include "CH455.h"
#include "LIN.h"

//当前步长
uint16_t currentStepSize = 0;
//当前循环次数
uint16_t currentCycleCount = 0;

volatile const uint8_t BCD_decode_tab[0x10] = { 0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F,
                                                0X77, 0X7C, 0X58, 0X5E, 0X79, 0X71 };

/**
 * 向CH455G写入数据
 * @param cmd
 * @param hi2c
 */
void CH455G_Write(uint16_t cmd, I2C_HandleTypeDef *hi2c)
{
    uint8_t data1=0;
    uint8_t data2=0;
    data1 = ((uint8_t)(cmd>>7)&CH455_I2C_MASK)|CH455_I2C_ADDR;
    data2 = (uint8_t)(cmd & 0x00ff);
    HAL_I2C_Master_Transmit(hi2c,data1,&data2,1,1000);
    __NOP();
}

/**
 * 初始化芯片参数
 * @param hi2c
 */
void CH455G_Init(I2C_HandleTypeDef *hi2c)
{
    CH455G_Write( CH455_SYSON , hi2c);// 开启显示和键盘，8段显示方式
    HAL_Delay(10);
    CH455G_Write( CH455_SYSON_8 , hi2c);    // 8级亮度显示
}

/**
 * 显示四位编码管的数字
 * @param data
 * @param hi2c
 */
void CH455G_Display(uint16_t data, I2C_HandleTypeDef *hi2c)
{
    uint8_t encode[4]={0};
    encode[0] = data / 1000;
    encode[1] = (data % 1000) / 100;
    encode[2] = (data % 100) / 10;
    encode[3] = data % 10;

    //发显示数据
    CH455G_Write( CH455_DIG0 | BCD_decode_tab[encode[0]] , hi2c);
    CH455G_Write( CH455_DIG1 | BCD_decode_tab[encode[1]] , hi2c);
    CH455G_Write( CH455_DIG2 | BCD_decode_tab[encode[2]] , hi2c);
    CH455G_Write( CH455_DIG3 | BCD_decode_tab[encode[3]] , hi2c);
}

/**
 * 更新编码管的数字
 * @param step
 * @param hi2c
 * @return
 */
uint16_t CH455G_Update_Data(uint8_t step, I2C_HandleTypeDef *hi2c)
{
    uint16_t result = 0;
    if (hi2c == STEP_DIGITAL_TUBE)
    {
        if (step)
        {
            result = ++currentStepSize;
        }
        else
        {
            result = --currentStepSize;
        }
    }
    if (hi2c == LOOP_DIGITAL_TUBE)
    {
        if (step)
        {
            result = ++currentCycleCount;
        }
        else
        {
            result = --currentCycleCount;
        }
    }
    return result;
}

