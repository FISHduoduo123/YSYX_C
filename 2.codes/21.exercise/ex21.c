#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

/*
数据类型	十进制打印宏	
 int8_t 	 PRId8 	       
 uint8_t 	 PRIu8 	       
 int32_t 	 PRId32 	   
 uint32_t 	 PRIu32 	   
 int64_t 	 PRId64 	  
 uint64_t 	 PRIu64 	   
 
 uint_least8_t 	 PRIuLEAST8
 int_least8_t 	 PRIdLEAST8 
 uint_least16_t 	 PRIuLEAST16
 int_least16_t 	 PRIdLEAST16
 uint_least32_t 	 PRIuLEAST32
 int_least32_t 	 PRIdLEAST32
 uint_least64_t 	 PRIuLEAST64
 int_least64_t 	 PRIdLEAST64

 uint_fast8_t 	 PRIuFAST8
 int_fast8_t 	 PRIdFAST8
 uint_fast16_t 	 PRIuFAST16
 int_fast16_t 	 PRIdFAST16
 uint_fast32_t 	 PRIuFAST32
 int_fast32_t 	 PRIdFAST32
 uint_fast64_t 	 PRIuFAST64
 int_fast64_t 	 PRIdFAST64

 intptr_t 	 PRIdPTR 	   
 uintptr_t 	 PRIuPTR

 uintmax_t 	 PRIuMAX
 intmax_t 	 PRIdMAX
 
*/

int main()
{
    // 8位无符号整形
    uint8_t unit8;
    unit8 = UINT8_MAX;
    printf("uint_max: %"PRIu8"\n",unit8); // 最大数
    // 8位有符号整形
    int8_t int8;
    int8 = INT8_MAX;
    printf("int_max: %"PRId8"\n",int8); // 最大数
    int8 = INT8_MIN;
    printf("int_min: %"PRId8"\n",int8); // 最小数

    // 16位无符号整形
    uint16_t uint16;
    uint16 = UINT16_MAX;
    printf("uint_max: %"PRIu16"\n",uint16); // 最大数
    // 16位有符号整形
    int16_t int16;
    int16 = INT16_MAX;
    printf("int_max: %"PRId16"\n",int16); // 最大数
    int16 = INT16_MIN;
    printf("int_min: %"PRId16"\n",int16); // 最小数

    // 32位无符号整形
    uint32_t uint32;
    uint32 = UINT32_MAX;
    printf("uint_max: %"PRIu32"\n",uint32); // 最大数
    // 32位有符号整形
    int32_t int32;
    int32 = INT32_MAX;
    printf("int_max: %"PRId32"\n",int32); // 最大数
    int32 = INT32_MIN;
    printf("int_min: %"PRId32"\n",int32); // 最小数

    // 64位无符号整形
    uint64_t uint64;
    uint64 = UINT64_MAX;
    printf("uint_max: %"PRIu64"\n",uint64); // 最大数
    // 64位有符号整形
    int64_t int64;
    int64 = INT64_MAX;
    printf("int_max: %"PRId64"\n",int64); // 最大数
    int64 = INT64_MIN;
    printf("int_min: %"PRId64"\n",int64); // 最小数

    // 至少8位无符号整形
    uint_least8_t uint_least8;
    uint_least8 = UINT_LEAST8_MAX;
    printf("uint_least8_max: %"PRIuLEAST8"\n",uint_least8); // 最大数
    // 至少8位有符号整形
    int_least8_t int_least8;
    int_least8 = INT_LEAST8_MAX;
    printf("int_least8_max: %"PRIdLEAST8"\n",int_least8); // 最大数
    int_least8 = INT_LEAST8_MIN;
    printf("int_least8_min: %"PRIdLEAST8"\n",int_least8); // 最小数

    // 至少16位无符号整形
    uint_least16_t uint_least16;
    uint_least16 = UINT_LEAST16_MAX;
    printf("uint_least16_max: %"PRIuLEAST16"\n",uint_least16); // 最大数
    // 至少16位有符号整形
    int_least16_t int_least16;
    int_least16 = INT_LEAST16_MAX;
    printf("int_least16_max: %"PRIdLEAST16"\n",int_least16); // 最大数
    int_least16 = INT_LEAST16_MIN;
    printf("int_least16_min: %"PRIdLEAST16"\n",int_least16); // 最小数

    // 至少32位无符号整形
    uint_least32_t uint_least32;
    uint_least32 = UINT_LEAST32_MAX;
    printf("uint_least32_max: %"PRIuLEAST32"\n",uint_least32); // 最大数
    // 至少32位有符号整形
    int_least32_t int_least32;
    int_least32 = INT_LEAST32_MAX;
    printf("int_least32_max: %"PRIdLEAST32"\n",int_least32); // 最大数
    int_least32 = INT_LEAST32_MIN;
    printf("int_least32_min: %"PRIdLEAST32"\n",int_least32); // 最小数

    // 至少64位无符号整形
    uint_least64_t uint_least64;
    uint_least64 = UINT_LEAST64_MAX;
    printf("uint_least64_max: %"PRIuLEAST64"\n",uint_least64); // 最大数
    // 至少64位有符号整形
    int_least64_t int_least64;
    int_least64 = INT_LEAST64_MAX;
    printf("int_least64_max: %"PRIdLEAST64"\n",int_least64); // 最大数
    int_least64 = INT_LEAST64_MIN;
    printf("int_least64_min: %"PRIdLEAST64"\n",int_least64); // 最小数

    // 快速8位无符号整形
    uint_fast8_t uint_fast8;
    uint_fast8 = UINT_FAST8_MAX;
    printf("uint_fast8_max: %"PRIuFAST8"\n",uint_fast8); // 最大数
    // 快速8位有符号整形
    int_fast8_t int_fast8;
    int_fast8 = INT_FAST8_MAX;
    printf("int_fast8_max: %"PRIdFAST8"\n",int_fast8); // 最大数
    int_fast8 = INT_FAST8_MIN;
    printf("int_fast8_min: %"PRIdFAST8"\n",int_fast8); // 最小数

    // 快速16位无符号整形
    uint_fast16_t uint_fast16;
    uint_fast16 = UINT_FAST16_MAX;
    printf("uint_fast16_max: %"PRIuFAST16"\n",uint_fast16); // 最大数
    // 快速16位有符号整形
    int_fast16_t int_fast16;
    int_fast16 = INT_FAST16_MAX;
    printf("int_fast16_max: %"PRIdFAST16"\n",int_fast16); // 最大数
    int_fast16 = INT_FAST16_MIN;
    printf("int_fast16_min: %"PRIdFAST16"\n",int_fast16); // 最小数

    // 快速32位无符号整形
    uint_fast32_t uint_fast32;
    uint_fast32 = UINT_FAST32_MAX;
    printf("uint_fast32_max: %"PRIuFAST32"\n",uint_fast32); // 最大数
    // 快速32位有符号整形
    int_fast32_t int_fast32;
    int_fast32 = INT_FAST32_MAX;
    printf("int_fast32_max: %"PRIdFAST32"\n",int_fast32); // 最大数
    int_fast32 = INT_FAST32_MIN;
    printf("int_fast32_min: %"PRIdFAST32"\n",int_fast32); // 最小数

    // 快速64位无符号整形
    uint_fast64_t uint_fast64;
    uint_fast64 = UINT_FAST64_MAX;
    printf("uint_fast64_max: %"PRIuFAST64"\n",uint_fast64); // 最大数
    // 快速64位有符号整形
    int_fast64_t int_fast64;
    int_fast64 = INT_FAST64_MAX;
    printf("int_fast64_max: %"PRIdFAST64"\n",int_fast64); // 最大数
    int_fast64 = INT_FAST64_MIN;
    printf("int_fast64_min: %"PRIdFAST64"\n",int_fast64); // 最小数

    // 指针大小的无符号整形
    uintptr_t uintptr;
    uintptr = UINTPTR_MAX;
    printf("uintptr_max: %"PRIuPTR"\n",uintptr); // 最大数
    // 指针大小的有符号整形
    intptr_t intptr;
    intptr = INTPTR_MAX;
    printf("intptr_max: %"PRIdPTR"\n",intptr); // 最大数
    intptr = INTPTR_MIN;
    printf("intptr_min: %"PRIdPTR"\n",intptr); // 最小数 

    // 系统相关的最大无符号整数类型
    uintmax_t uintmax;
    uintmax = UINTMAX_MAX;
    printf("uintmax_max: %"PRIuMAX"\n",uintmax); // 最大数
    // 系统相关的最大有符号整数类型
    intmax_t intmax;
    intmax = INTMAX_MAX;
    printf("intmax_max: %"PRIdMAX"\n",intmax); // 最大数
    intmax = INTMAX_MIN;
    printf("intmax_min: %"PRIdMAX"\n",intmax); // 最小数
    
    // 计算intmax_t类型的大小
    size_t size = sizeof(intmax_t);
    printf("size of intmax_t: %zu\n", size);

    return 0;
}
