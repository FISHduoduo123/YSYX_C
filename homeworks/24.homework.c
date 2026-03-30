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

char *shrink_space(char *dest, const char *src, size_t n);
各项参数和返回值的含义和strncpy类似。完成之后，为自己实现的函数写一个Man Page。
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
