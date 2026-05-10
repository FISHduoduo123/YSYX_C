/*实现一个功能更完整的printf，能够识别%，能够处理%d、%f对应的整数参数。*/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int myprintf(char *d, ...) {
    va_list ap;
    va_start(ap, d);
    if (d == NULL) return 0;

    for (int i = 0; d[i] != '\0'; i++) {
        if (d[i] == '%') {
            switch (d[i + 1]) {
                case 'd': {
                    char buf[20];
                    int num = va_arg(ap, int);
                    if (num < 0) {
                        num = -num;
                        putchar('-');
                    }
                    // 将整数转换为字符串（逆序存入）
                    int idx = 0;
                    if (num == 0) {
                        buf[idx++] = '0';
                    } else {
                        while (num > 0) {
                            buf[idx++] = '0' + (num % 10);
                            num /= 10;
                        }
                    }
                    // 反转输出
                    for (int j = idx - 1; j >= 0; j--)
                        putchar(buf[j]);
                    break;
                }
                case 'f': {
                    char buf[20];
                    double num = va_arg(ap, double);   // 修正类型
                    if (num < 0) {
                        num = -num;
                        putchar('-');
                    }
                    // 提取整数部分并保存
                    long int_part = (long)num;
                    long temp = int_part;   // 保存原始整数部分用于转换
                    // 整数部分转换
                    int idx = 0;
                    if (temp == 0) {
                        buf[idx++] = '0';
                    } else {
                        while (temp > 0) {
                            buf[idx++] = '0' + (temp % 10);
                            temp /= 10;
                        }
                    }
                    for (int j = idx - 1; j >= 0; j--)
                        putchar(buf[j]);
                    
                    // 输出小数点
                    putchar('.');
                    
                    // 计算小数部分
                    double frac = num - int_part;   // 使用原始的 int_part
                    // 输出六位小数（截断）
                    for (int k = 0; k < 6; k++) {
                        frac *= 10;
                        int digit = (int)frac;
                        putchar('0' + digit);
                        frac -= digit;
                    }
                    break;
                }
                default:
                    putchar(d[i]);   // 未知格式，原样输出
                    break;
            }
            i++;  // 跳过格式字符
        } else {
            putchar(d[i]);
        }
    }
    va_end(ap);
    return 0;  // 可返回输出字符数，此处简化
}

int main(void) {
    myprintf("%d%f\n", 1, -1.1);
    return 0;
}
