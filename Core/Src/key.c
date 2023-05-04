//
// Created by 陈骏骏 on 2023/5/3.
//

#include "key.h"

/**
 * 普通按键的检测
 * @param GPIOx
 * @param GPIO_Pin
 * @return
 */
uint8_t General_Key_Scan(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin)
{
    /*检测是否有按键按下 */
    if (HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON )
    {
        /*等待按键释放 */
        while (HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON);
        return KEY_ON;
    }
    else
    {
        return KEY_OFF;
    }
}

/**
 * 运算按键的检测
 * @param GPIOx
 * @param GPIO_Pin
 * @param Number_Of_Symbols
 */
void Operation_Key_Scan(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin,uint8_t step,uint8_t NixieTube_Number)
{
    /*检测是否有按键按下 */
    if (HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON )
    {
        /*等待按键释放 */
        while (HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON)
        {
            //长按运算按键时，数码管累加或者累减1
            if (NixieTube_Number)
            {
                //循环数码管
            }
            else
            {
                //步长数码管
            }
            //延迟100ms,再次检测
            HAL_Delay(100);
        }
    }
}