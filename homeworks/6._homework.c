/*
循环变量：作为控制变量，每轮数值改变，并下一轮开始前在控制表达式进行判断用于跟踪循环次数
累加器（加法/乘法计算根据实现目标逻辑而定）：用于累计所经过循环后的总量
(a%10)取个位
(a/10)取十位
例子：统计1~100中9出现的次数*/
#include <stdio.h>
int main() 
{
    int i = 1;     //循环控制变量
    int count = 0; //累加器统计9出现次数
    while (i <= 100) 
    {
        if (i % 10 == 9) count++; // 取个位
        if (i / 10 == 9) count++;  // 取十位
        i++;
    }
    printf("9出现次数：%d\n", count);
    
    return 0;
}

//求两个正整数a和b的最大公约数（GCD，Greatest Common Divisor），
//使用Euclid算法：
/*
  1.如果a除以b能整除，则最大公约数是b。
  2.否则，最大公约数等于b和a%b的最大公约数。
*/
#include <stdio.h> 
int main(void)
{   
    int a = 10; 
    int b = 2;      //初始a, b   
    int c = 0;      //计算结果   
    while (a%b)
    {
        a = b;
        b = a%b;    //下一次循环操作数
    }
    c = b;        //输出结果
    printf("最大公约数%d\n",c);
    return 0;
}

//求Fibonacci数列的第n项，
//这个数列是这样定义的：
/*
  fib(0)=1
  fib(1)=1
  fib(n)=fib(n-1)+fib(n-2)
*/
#include <stdio.h> 
int main(void)
{   
    int n = 4;      //初始n   
    int cnt = 0;
    int a = 0;
    int b = 1;      //中间结果
    int c = 0;      //计算结果   
    while (cnt < n)
    {
        if (n==0||n==1) break;
        a = a + b;
        a = a^b;
        b = a^b;    
        a = a^b;    //a, b交换数据,b为最新结果
        cnt = cnt + 1;
    }
    c = b;  //输出结果
    printf("斐波那契求和结果为%d\n",c);
    return 0;
}

//编写程序数一下1到100的所有整数中出现多少次数字
#include <stdio.h> 
int main(void)
{   
    int i = 1;
    int cnt = 0;
    while (i<=100)
    {
        if (i<10) cnt+=1;       //1~9每次出现1个数字
        else if (i<100) cnt+=2; //10~99每次出现2个数字
        else cnt+=3;            //100出现3个数字
        i++;
    }
    printf("1~100总共出现了%d个数字\n",cnt);//一共出现了192个数字
    return 0;
}

/*求素数这个程序只是为了说明break和continue的用法才这么写的，
其实完全可以不用break和continue，请读者修改一下控制流程，
去掉break和continue而保持功能不变。*/
#include <stdio.h>
int main() 
{
    // 打印1~100所有素数，大于1并且只能被自身和1整除的自然数
    for(int i=1;i<=100;i++) 
    {
        int s = 1; // 1=素数 
        int j = 1; //循环变量
        while (j<=100)
        {
            if (!(i%j)&&(j!=1)&&(j!=i)) 
            {
                s = 0;   //设置非素数
                j = 100; //设置循环变量最大值结束循环
            }
            j++;
        }
        if (s&&(i>1)) printf("素数：%d\n", i); //素数
        else s = 1;  
    }
    
    return 0;
}

/*上一节讲过怎样把for循环改写成等价的while循环，
但也提到如果循环体中有continue语句这两种形式就不等价了，
想一想为什么不等价了？
    while循环的循环变量是在语句块内赋值，若赋值前遇到continue则重新开始循环，循环变量不变
    for循环循环变量赋值在判断括号内，遇到continue则会重新开始循环，同时循环变量进行赋值，
    这两种循环面对continue不同处理逻辑会导致无法等价。
*/

/*
上面打印的小九九有一半数据是重复的，因为8*9和9*8的结果一样。请修改程序打印这样的小九九：
1	
2	4	
3	6	9	
4	8	12	16	
5	10	15	20	25	
6	12	18	24	30	36	
7	14	21	28	35	42	49	
8	16	24	32	40	48	56	64	
9	18	27	36	45	54	63	72	81
*/
#include <stdio.h>
int main() 
{
    // 打印1~100所有素数
    for(int i=1;i<=9;i++) 
    {
        for(int j=1;j<=i;j++) printf("%d\t",(i*j));
        printf("\n");
    }
    return 0;
}
/*编写函数diamond打印一个菱形。如果调用diamond(3, '*')则打印：
	*
*	*	*
	*
*/
#include <stdio.h>
void iamond(int num_char,char a)
{
    if ((num_char+1)%2) printf("请输入奇数");
    int cnt_tab = num_char/2; // 求初始空缺数
    //字符数递增
    for(int i=1;i<=num_char;i+=2) 
    {
        for (int tab=1;tab<=cnt_tab;tab++) printf("\t");
        cnt_tab --; // 更新空缺数
        for (int cnt_char=1;cnt_char<=i;cnt_char++) printf("%c\t",a);
        printf("\n");
    }
    cnt_tab = 1;
    //字符数递减
    for(int i=num_char-2;i>=1;i-=2) 
    {
        for (int tab=1;tab<=cnt_tab;tab++) printf("\t");
        cnt_tab ++; // 更新空缺数
        for (int cnt_char=1;cnt_char<=i;cnt_char++) printf("%c\t",a);
        printf("\n");
    }
    
}
int main() 
{
    iamond(5,'a');
    return 0;
}











