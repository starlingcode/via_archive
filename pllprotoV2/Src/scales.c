#include "scales.h"

#include "main.h"

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"



const ScaleNote harmSubharm1[128] = {ratio1_320, ratio1_320, ratio1_320, ratio1_320, ratio1_256, ratio1_256, ratio1_256, ratio1_256, ratio1_192, ratio1_192, ratio1_192, ratio1_192, ratio1_192,
ratio1_192, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio1_64, ratio1_64,
ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_56, ratio1_56, ratio1_48, ratio1_48, ratio1_48, ratio1_40,
ratio1_40, ratio1_40, ratio1_40, ratio1_32, ratio1_32, ratio1_32, ratio1_32, ratio1_24, ratio1_24, ratio1_24, ratio1_24, ratio1_24,
ratio1_24, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_7, ratio1_7, ratio1_6, ratio1_6, ratio1_6, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_1, ratio1_1,
ratio1_1, ratio1_1, ratio1_1, ratio8_8, ratio8_8, ratio8_8, ratio8_7, ratio8_7, ratio8_6, ratio8_6, ratio8_6, ratio8_5,
ratio8_5, ratio8_5, ratio8_5, ratio8_4, ratio8_4, ratio8_4, ratio8_4, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3,
ratio8_3, ratio8_2, ratio8_2, ratio8_2, ratio8_2, ratio8_2, ratio8_2};

const ScaleNote harmSubharm2[128] = {ratio2_320, ratio2_320, ratio2_320, ratio2_320, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio2_192, ratio2_192, ratio2_192, ratio2_192, ratio2_192,
ratio2_192, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio2_64, ratio2_64,
ratio2_64, ratio2_64, ratio2_64, ratio1_32, ratio1_32, ratio1_32, ratio2_56, ratio2_56, ratio1_24, ratio1_24, ratio1_24, ratio2_40,
ratio2_40, ratio2_40, ratio2_40, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio2_24, ratio2_24, ratio2_24, ratio2_24, ratio2_24,
ratio2_24, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio2_8, ratio2_8,
ratio2_8, ratio2_8, ratio2_8, ratio1_4, ratio1_4, ratio1_4, ratio2_7, ratio2_7, ratio1_3, ratio1_3, ratio1_3, ratio2_5,
ratio2_5, ratio2_5, ratio2_5, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3,
ratio2_3, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio2_1, ratio2_1,
ratio2_1, ratio2_1, ratio2_1, ratio8_4, ratio8_4, ratio8_4, ratio16_7, ratio16_7, ratio8_3, ratio8_3, ratio8_3, ratio16_5,
ratio16_5, ratio16_5, ratio16_5, ratio8_2, ratio8_2, ratio8_2, ratio8_2, ratio16_3, ratio16_3, ratio16_3, ratio16_3, ratio16_3,
ratio16_3, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1};

const ScaleNote harmSubharm3[128] = {ratio3_512, ratio3_512, ratio3_512, ratio3_512, ratio3_512, ratio3_512, ratio3_256, ratio3_256, ratio3_256, ratio3_256, ratio3_256, ratio3_256, ratio3_256,
ratio3_256, ratio3_256, ratio3_256, ratio3_128, ratio3_128, ratio3_128, ratio3_128, ratio3_128, ratio3_128, ratio3_128, ratio3_128, ratio3_128,
ratio3_128, ratio3_112, ratio3_112, ratio1_32, ratio1_32, ratio1_32, ratio3_80, ratio3_80, ratio3_80, ratio3_80, ratio3_64, ratio3_64,
ratio3_64, ratio3_64, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio3_32, ratio3_32, ratio3_32, ratio3_32, ratio3_32,
ratio3_32, ratio3_32, ratio3_32, ratio3_32, ratio3_32, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16,
ratio3_16, ratio3_16, ratio3_16, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8,
ratio3_8, ratio3_7, ratio3_7, ratio1_2, ratio1_2, ratio1_2, ratio3_5, ratio3_5, ratio3_5, ratio3_5, ratio3_4, ratio3_4,
ratio3_4, ratio3_4, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2,
ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1,
ratio3_1, ratio3_1, ratio3_1, ratio48_8, ratio48_8, ratio48_8, ratio48_8, ratio48_8, ratio48_8, ratio48_8, ratio48_8, ratio48_8,
ratio48_8, ratio48_7, ratio48_7, ratio16_2, ratio16_2, ratio16_2, ratio48_5};

const ScaleNote harmSubharm4[128] = {ratio4_320, ratio4_320, ratio4_320, ratio4_320, ratio1_64, ratio1_64, ratio1_64, ratio4_192, ratio4_192, ratio4_192, ratio4_192, ratio4_192, ratio4_192,
ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio4_64, ratio4_64,
ratio4_64, ratio4_64, ratio4_64, ratio1_16, ratio1_16, ratio1_16, ratio4_56, ratio4_56, ratio2_24, ratio2_24, ratio2_24, ratio4_40,
ratio4_40, ratio4_40, ratio4_40, ratio1_8, ratio1_8, ratio1_8, ratio4_24, ratio4_24, ratio4_24, ratio4_24, ratio4_24, ratio4_24,
ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio4_8, ratio4_8,
ratio4_8, ratio4_8, ratio4_8, ratio1_2, ratio1_2, ratio1_2, ratio4_7, ratio4_7, ratio2_3, ratio2_3, ratio2_3, ratio4_5,
ratio4_5, ratio4_5, ratio4_5, ratio1_1, ratio1_1, ratio1_1, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3,
ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio4_1, ratio4_1,
ratio4_1, ratio4_1, ratio4_1, ratio8_2, ratio8_2, ratio8_2, ratio32_7, ratio32_7, ratio16_3, ratio16_3, ratio16_3, ratio32_5,
ratio32_5, ratio32_5, ratio32_5, ratio8_1, ratio8_1, ratio8_1, ratio32_3, ratio32_3, ratio32_3, ratio32_3, ratio32_3, ratio32_3,
ratio16_1, ratio16_1, ratio16_1, ratio16_1, ratio16_1, ratio16_1, ratio16_1};

const ScaleNote harmSubharm5[128] = {ratio5_512, ratio5_512, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256,
ratio5_256, ratio5_256, ratio5_256, ratio5_128, ratio5_128, ratio5_128, ratio5_128, ratio5_128, ratio5_128, ratio5_128, ratio5_112, ratio5_112,
ratio5_96, ratio5_96, ratio5_96, ratio1_16, ratio1_16, ratio5_64, ratio5_64, ratio5_64, ratio5_64, ratio5_48, ratio5_48, ratio5_48,
ratio5_48, ratio5_48, ratio5_48, ratio5_32, ratio5_32, ratio5_32, ratio5_32, ratio5_32, ratio5_32, ratio5_32, ratio5_32, ratio5_32,
ratio5_32, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16,
ratio5_16, ratio5_16, ratio5_16, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_7, ratio5_7,
ratio5_6, ratio5_6, ratio5_6, ratio1_1, ratio1_1, ratio5_4, ratio5_4, ratio5_4, ratio5_4, ratio5_3, ratio5_3, ratio5_3,
ratio5_3, ratio5_3, ratio5_3, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2,
ratio5_2, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1,
ratio5_1, ratio5_1, ratio5_1, ratio80_8, ratio80_8, ratio80_8, ratio80_8, ratio80_8, ratio80_8, ratio80_8, ratio80_7, ratio80_7,
ratio80_6, ratio80_6, ratio80_6, ratio16_1, ratio16_1, ratio80_4, ratio80_4};

const ScaleNote harmSubharm6[128] = {ratio3_256, ratio3_256, ratio3_256, ratio3_256, ratio3_256, ratio3_256, ratio6_256, ratio6_256, ratio6_256, ratio6_256, ratio6_256, ratio6_256, ratio6_256,
ratio6_256, ratio6_256, ratio6_256, ratio3_64, ratio3_64, ratio3_64, ratio3_64, ratio3_64, ratio3_64, ratio3_64, ratio3_64, ratio3_64,
ratio3_64, ratio6_112, ratio6_112, ratio1_16, ratio1_16, ratio6_80, ratio6_80, ratio6_80, ratio6_80, ratio3_32, ratio3_32, ratio3_32,
ratio3_32, ratio2_16, ratio2_16, ratio2_16, ratio2_16, ratio2_16, ratio2_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16,
ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio6_16, ratio6_16, ratio6_16, ratio6_16, ratio6_16, ratio6_16, ratio6_16,
ratio6_16, ratio6_16, ratio6_16, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4,
ratio3_4, ratio6_7, ratio6_7, ratio1_1, ratio1_1, ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio3_2, ratio3_2, ratio3_2,
ratio3_2, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1,
ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1,
ratio6_1, ratio6_1, ratio6_1, ratio48_4, ratio48_4, ratio48_4, ratio48_4, ratio48_4, ratio48_4, ratio48_4, ratio48_4, ratio48_4,
ratio48_4, ratio96_7, ratio96_7, ratio16_1, ratio16_1, ratio96_5, ratio96_5};

const ScaleNote harmSubharm7[128] = {ratio7_512, ratio7_512, ratio7_512, ratio7_512, ratio7_512, ratio7_512, ratio7_512, ratio7_512, ratio7_256, ratio7_256, ratio7_256, ratio7_256, ratio7_256,
ratio7_256, ratio7_256, ratio7_256, ratio7_128, ratio7_128, ratio7_128, ratio7_128, ratio7_128, ratio7_128, ratio7_128, ratio7_128, ratio7_128,
ratio7_128, ratio7_128, ratio7_128, ratio1_16, ratio1_16, ratio7_96, ratio7_96, ratio7_80, ratio7_80, ratio7_80, ratio7_80, ratio7_64,
ratio7_64, ratio7_64, ratio7_64, ratio7_48, ratio7_48, ratio7_48, ratio7_48, ratio7_48, ratio7_48, ratio7_32, ratio7_32, ratio7_32,
ratio7_32, ratio7_32, ratio7_32, ratio7_32, ratio7_32, ratio7_32, ratio7_32, ratio7_16, ratio7_16, ratio7_16, ratio7_16, ratio7_16,
ratio7_16, ratio7_16, ratio7_16, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8,
ratio7_8, ratio7_8, ratio7_8, ratio1_1, ratio1_1, ratio7_6, ratio7_6, ratio7_5, ratio7_5, ratio7_5, ratio7_5, ratio7_4,
ratio7_4, ratio7_4, ratio7_4, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_2, ratio7_2, ratio7_2,
ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1,
ratio7_1, ratio7_1, ratio7_1, ratio112_8, ratio112_8, ratio112_8, ratio112_8, ratio112_8, ratio112_8, ratio112_8, ratio112_8, ratio112_8,
ratio112_8, ratio112_8, ratio112_8, ratio16_1, ratio16_1, ratio112_6, ratio112_6};

const ScaleNote harmSubharm8[128] = {ratio8_320, ratio8_320, ratio8_320, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio8_192, ratio8_192, ratio8_192, ratio8_192, ratio8_192, ratio8_192,
ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio8_64, ratio8_64,
ratio8_64, ratio8_64, ratio8_64, ratio1_8, ratio1_8, ratio8_56, ratio8_56, ratio4_24, ratio4_24, ratio4_24, ratio8_40, ratio8_40,
ratio8_40, ratio8_40, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio8_24, ratio8_24, ratio8_24, ratio8_24, ratio8_24, ratio8_24,
ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio8_8, ratio8_8,
ratio8_8, ratio8_8, ratio8_8, ratio1_1, ratio1_1, ratio8_7, ratio8_7, ratio4_3, ratio4_3, ratio4_3, ratio8_5, ratio8_5,
ratio8_5, ratio8_5, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3,
ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio8_1, ratio8_1,
ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio64_7, ratio64_7, ratio32_3, ratio32_3, ratio32_3, ratio64_5, ratio64_5,
ratio64_5, ratio64_5, ratio16_1, ratio16_1, ratio16_1, ratio16_1, ratio64_3, ratio64_3, ratio64_3, ratio64_3, ratio64_3, ratio64_3,
ratio32_1, ratio32_1, ratio32_1, ratio32_1, ratio32_1, ratio32_1, ratio32_1};




const ScaleNote *harmSubharm[8] = {harmSubharm1, harmSubharm2, harmSubharm3, harmSubharm4, harmSubharm5, harmSubharm6, harmSubharm7, harmSubharm8};

