# 五、深入理解函数
## 1.return语句  
  在有返回值的函数中，return语句的作用是**提供整个函数的返回值，并结束当前函数返回到调用它的地方**。在没有返回值的函数中也可以使用return语句，例如当检查到一个错误时提前结束当前函数的执行并返回：
```
#include <math.h>
void print_logarithm(double x)
{
	if (x <= 0.0) {
		printf("Positive numbers only, please.\n");
		return;
	}
	printf("The log of x is %f", log(x));
}
```
  函数的返回值应该这样理解：**函数返回一个值相当于定义一个和返回值类型相同的临时变量并用return后面的表达式来初始化**。
注意：
  1.函数的返回值不是左值，或者说函数调用表达式不能做左值，因此下面的赋值语句是非法的：
```
is_even(20) = 1;  
```
  2.在写带有return语句的函数时要小心检查所有的代码路径（Code Path）。有些代码路径在任何条件下都执行不到，这称为Dead Code，例如把&&和||运算符记混了（据我了解初学者犯这个低级错误的不在少数），写出如下代码：
```
void foo(int x, int y)
{
	if (x >= 0 || y >= 0) {
		printf("both x and y are positive.\n");
		return;
	} else if (x < 0 || y < 0) {
		printf("both x and y are negetive.\n");
		return;
	}
	printf("x has a different sign from y.\n");
}
```
最后一行printf永远都没机会被执行到，是一行Dead Code。  







  
