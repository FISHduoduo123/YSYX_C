//自己实现一个strcpy函数，尽可能简洁，按照本书的编码风格你能用三行代码写出函数体吗？
#include <stdio.h>
void strcpy(char * a,char * b)
{   
    int num = 0;
    for (int i=0;b[i]!='\0';i++) 
    {
        num = i;
        a[i] = b[i];
    }
    a[num+1] = '\0';
}

int main(void)
{
    char a[3]="hi";
    char b[3];
    strcpy(b,a);
    printf("%s\n",b);
    return 0;
}
/*
编一个函数，输入一个字符串，要求做一个新字符串，把其中所有的一个或多个连续的空白字符都压缩为一个空格。这里所说的空白包括空格、'\t'、'\n'、'\r'。例如原来的字符串是：

This Content hoho       is ok
        ok?

        file system
uttered words   ok ok      ?
end.
压缩了空白之后就是：

This Content hoho is ok ok? file system uttered words ok ok ? end.
实现该功能的函数接口要求符合下述规范：
*/
#include <stdio.h>
#include <string.h>

char *shrink_space(char *dest, const char *src, size_t n)
{
    int num;
    for (int i=0;i<n;i++)
    {
        dest[i] = src[i];
        num = i;
    }
    dest[num+1] = '\0';
    return dest;
}

int main(void) {
    char dest[5];
    char s[4] = "123";
    printf("data:%s\n",shrink_space(dest,s,3));
    return 0;
}
/*写一个插入排序的函数和一个折半查找的函数。*/
#include <stdio.h>
void swap (int*a,int*b)
{
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;
}
int* sort (int*arr,int len)
{
    if (len<=0) 
    {
        printf("长度错误\n");
        return arr;
    }
    // 比较
    for (int i=0;i<len-1;i++)
    {
        if (arr[i]>arr[i+1])
        {
            swap(&arr[i],&arr[i+1]);
            for (int j=i;j>0;j--)
            {
                if (arr[j-1]>arr[j]) swap(&arr[j-1],&arr[j]);
                else continue;
            }
        }
    }
    return arr;
}

int* search(int* arr, int d, int len) {
    int start = 0;
    int last = len - 1;
    while (start <= last) {
        int mid = start + (last - start) / 2;  // 防止溢出
        if (arr[mid] == d) {
            return &arr[mid];
        } else if (arr[mid] > d) {
            last = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    return NULL;  // 未找到
}

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
    myprintf("%d%f", 1, -1.1);
    return 0;
}
