//
// Created by 陈骏骏 on 2023/5/4.
//

#ifndef PRODUCTMANUALTEST_CH455_H
#define PRODUCTMANUALTEST_CH455_H

#include "main.h"
#include "i2c.h"

#define STEP_DIGITAL_TUBE           &hi2c2
#define LOOP_DIGITAL_TUBE           &hi2c1

// 设置系统参数命令
#define CH455_BIT_ENABLE    0x01        // 开启/关闭位
#define CH455_BIT_SLEEP        0x04        // 睡眠控制位
#define CH455_BIT_7SEG        0x08        // 7段控制位
#define CH455_BIT_INTENS1    0x10        // 1级亮度
#define CH455_BIT_INTENS2    0x20        // 2级亮度
#define CH455_BIT_INTENS3    0x30        // 3级亮度
#define CH455_BIT_INTENS4    0x40        // 4级亮度
#define CH455_BIT_INTENS5    0x50        // 5级亮度
#define CH455_BIT_INTENS6    0x60        // 6级亮度
#define CH455_BIT_INTENS7    0x70        // 7级亮度
#define CH455_BIT_INTENS8    0x00        // 8级亮度

#define CH455_SYSOFF    0x0400            // 关闭显示、关闭键盘
#define CH455_SYSON        ( CH455_SYSOFF | CH455_BIT_ENABLE )    // 开启显示、键盘
#define CH455_SLEEPOFF    CH455_SYSOFF    // 关闭睡眠
#define CH455_SLEEPON    ( CH455_SYSOFF | CH455_BIT_SLEEP )    // 开启睡眠
#define CH455_7SEG_ON    ( CH455_SYSON | CH455_BIT_7SEG )    // 开启七段模式
#define CH455_8SEG_ON    ( CH455_SYSON | 0x00 )    // 开启八段模式
#define CH455_SYSON_4    ( CH455_SYSON | CH455_BIT_INTENS4 )    // 开启显示、键盘、4级亮度
#define CH455_SYSON_8    ( CH455_SYSON | CH455_BIT_INTENS8 )    // 开启显示、键盘、8级亮度

// 加载字数据命令
#define CH455_DIG0        0x1400            // 数码管位0显示,需另加8位数据
#define CH455_DIG1        0x1500            // 数码管位1显示,需另加8位数据
#define CH455_DIG2        0x1600            // 数码管位2显示,需另加8位数据
#define CH455_DIG3        0x1700            // 数码管位3显示,需另加8位数据

// CH455接口定义
#define        CH455_I2C_ADDR        0x40            // CH455的地址
#define        CH455_I2C_MASK        0x3E            // CH455的高字节命令掩码

#define BCD_decode_DP   0x0080
#define BCD_decode_NG   0x0040

//当前步长
extern uint16_t currentStepSize;
//当前循环次数
extern uint16_t currentCycleCount;

void CH455G_Write(uint16_t cmd, I2C_HandleTypeDef *hi2c);
void CH455G_Init(I2C_HandleTypeDef *hi2c);
void CH455G_Display(uint16_t data, I2C_HandleTypeDef *hi2c);
uint16_t CH455G_Update_Data(uint8_t step, I2C_HandleTypeDef *hi2c);

#endif //PRODUCTMANUALTEST_CH455_H
