/*编写一个程序，定义两个类型和长度都相同的数组，将其中一个数组的所有元素拷贝给另一个。
既然数组不能直接赋值，想想应该怎么实现。*/
#include <stdio.h>
int main(void)
{
	int a[10], b[10];
    for(int i=0;i<10;i++) b[i] = a [i];
	return 0;
}

//用rand函数生成[10, 20]之间的随机整数，表达式应该怎么写？
#include <stdio.h>
#include <stdlib.h>
int rand_10_to_20(void)
{   
    int a;
    while(1) 
    {
        a = rand();
        if((a>=10)&&(a<=20))
        {
            return a;
        }
    }
}
int main(void)
{
    for(int i=0;i<10;i++) 
    {
        printf("Rand:%d\n",rand_10_to_20());
    }
	return 0;
}

//以可视化的形式打印直方图
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct int_list {int a[10];};
struct int_list rand_list(struct int_list z)
{   
    for(int i=0;i<10;i++)
    {
        z.a[i] = rand()%10;
    }
    for(int i=0;i<10;i++) printf("%d\t",z.a[i]);//debug
    printf("\n");
    return z;
}
struct int_list howmany(struct int_list z)
{
    for(int i=0;i<10;i++)
    {
        printf("%d:\t",i);
        int cnt = 0;
        for(int j=0;j<10;j++) if(z.a[j]==i) cnt++; // 统计数量
        for(int j=cnt;j>0;j--) printf("*\t");	//打印*
        printf("\n");
    }
}
int main(void)
{
    srand(time(NULL));
    struct int_list list;
    list = rand_list(list);
    howmany(list);
	return 0;
}

//定义一个数组，编程打印它的全排列
/*
#define N 3
int a[N] = { 1, 2, 3 };
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4
int a[N] = { 1, 2, 3, 4};

void list(int basic)
{
    //判断否抵达索引边界并打印当前排列数组
    if(basic==N-1) 
    {
        for(int i=0;i<N;i++)printf("%d",a[i]);
        printf("\n");
        return;
    }
    for(int j=basic;j<N;j++)
    {
        int swap = 0;
        //将当前基元素与遍历元素替换
        swap = a[basic];
        a[basic] = a[j];
        a[j] = swap;
        list(basic+1);  // 移动至下一个基元素
        //恢复初始数组
        swap = a[basic];
        a[basic] = a[j];
        a[j] = swap;
    }
    return;
}
int main(void)
{
    list(0);
    return 0;
}
