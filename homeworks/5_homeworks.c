//编写一个布尔函数int is_leap_year(int year)，
//判断参数year是不是闰年。如果某年份能被4整除，但不能被100整除，那么这一年就是闰年，
//此外，能被400整除的年份也是闰年。
#include <stdio.h> 
int is_leap_year(int year)
{
    return (!(year%4)&&(year%100))||!(year%400);
}
int main(void)
{   
    int i;
    i = 2017;
    if (is_leap_year(i)) printf("闰年\n");
    else printf("平年\n");
	return 0;
}
//编写一个函数double myround(double x)，
//输入一个小数，将它四舍五入。
//例如myround(-3.51)的值是-4.0，myround(4.49)的值是4.0。可以调用math.h中的库函数ceil和floor实现这个函数。
#include <stdio.h> 
#include <math.h> 
double myround(double x)
{
    if (x>0) return floor(x+0.5);
    else if (x<0) return floor(x-0.5);
    else return 0;
}
int main(void)
{   
    int i;
    i = 2.6;
    printf("四舍五入后：%f\n",myround(i));
	return 0;
}

//编写递归函数求两个正整数a和b的最大公约数（GCD），
/*使用Euclid算法：
	1.如果a除以b能整除，则最大公约数是b。
	2.否则，最大公约数等于b和a%b的最大公约数。
*/
#include <stdio.h> 
int gcd(int a,int b)
{
    if (a%b) return gcd(b,a%b);
    else return b;
}
int main(void)
{   
    int a, b;
    a = 10;
    b = 4;
    printf("a和b最大公约数为%d\n",gcd(a,b));
    return 0;
}
//编写递归函数求Fibonacci数列的第n项，这个数列是这样定义的：
/*fib(0)=1
fib(1)=1
fib(n)=fib(n-1)+fib(n-2)
*/
#include <stdio.h> 
int fid(int a)
{
    if (a==0||a==1) return 1;
    else return fid(a-1) + fid(a-2);
}
int main(void)
{   
    int a=3;
    printf("Fibonacci数列的第%d项为%d\n",a,fid(a));
    return 0;
}

