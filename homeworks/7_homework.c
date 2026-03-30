/*
在本节的基础上实现一个打印复数的函数，打印的格式是x+yi，
如果实部或虚部为0则省略，例如：1.0、-2.0i、-1.0+2.0i、1.0-2.0i。
最后编写一个main函数测试本节的所有代码。想一想这个打印函数应该属于上图中的哪一层？
*/
#include <stdio.h>
#include <math.h>
// 提供复数存储表示层
//复数变量类型
struct complex_struct {
	double x, y;
};
//复数直角坐标提取
double real_part(struct complex_struct z)
{
	return z.x;
}
double img_part(struct complex_struct z)
{
	return z.y;
}
//复数极坐标提取
double magnitude(struct complex_struct z)
{
	return sqrt(z.x * z.x + z.y * z.y);
}
double angle(struct complex_struct z)
{
	return atan2(z.y, z.x);
}
//复数构造
struct complex_struct make_from_real_img(double x, double y)
{
	struct complex_struct z;
	z.x = x;
	z.y = y;
	return z;
}
struct complex_struct make_from_mag_ang(double r, double A)
{
	struct complex_struct z;
	z.x = r * cos(A);
	z.y = r * sin(A);
	return z;
}
//提供复数运算层
struct complex_struct add_complex(struct complex_struct z1, struct complex_struct z2)
{
	return make_from_real_img(real_part(z1) + real_part(z2),
				  img_part(z1) + img_part(z2));
}

struct complex_struct sub_complex(struct complex_struct z1, struct complex_struct z2)
{
	return make_from_real_img(real_part(z1) - real_part(z2),
				  img_part(z1) - img_part(z2));
}

struct complex_struct mul_complex(struct complex_struct z1, struct complex_struct z2)
{
	return make_from_mag_ang(magnitude(z1) * magnitude(z2),
				 angle(z1) + angle(z2));
}

struct complex_struct div_complex(struct complex_struct z1, struct complex_struct z2)
{
	return make_from_mag_ang(magnitude(z1) / magnitude(z2),
				 angle(z1) - angle(z2));
}

//复数打印(属于第二层，调用底层存储层并执行数据操作)
void complex_print(struct complex_struct z1)
{   
    printf("%f+%fi/n",real_part(z1),img_part(z1));
}

int main(void)
{
    struct complex_struct a = {1.0,1.0};    // 定义并初始化复数变量 a
    complex_print(a);   // 打印 a
    struct complex_struct b = {2.0,2.0};    // 定义并初始化复数变量 b
    complex_print(b);   // 打印 b

    //运算操作并打印
    complex_print(add_complex(a,b));    // add
    complex_print(sub_complex(a,b));    // sub
    complex_print(mul_complex(a,b));    // mul
    complex_print(div_complex(a,b));    // div
    return 0;
}

/*
实现一个用分子分母的格式来表示有理数的结构体rational以及相关的函数，
rational结构体之间可以做加减乘除运算，
运算的结果仍然是rational。测试代码如下：
    int main(void)
{
	struct rational a = make_rational(1, 8);  a=1/8 
	struct rational b = make_rational(-1, 8);  b=-1/8 
	print_rational(add_rational(a, b));
	print_rational(sub_rational(a, b));
	print_rational(mul_rational(a, b));
	print_rational(div_rational(a, b));

	return 0;
}
注意要约分为最简分数，例如1/8和-1/8相减的打印结果应该是1/4而不是2/8，
可以利用第 3 节 “递归”练习题中的Euclid算法来约分。
在动手编程之前先思考一下这个问题实现了什么样的数据抽象，抽象层应该由哪些函数组成。
*/
#include <stdio.h>
//取绝对值
int abs(int a)
{
    if (a<0) return -a;
    else return a;
}
// 提供分数存储表示层
//分数变量类型
struct rational {int x, y;};
//分子提取
int num_part(struct rational z)
{
	return z.x;
}
//分母提取
int den_part(struct rational z)
{
	return z.y;
}
//分数构造
struct rational make_rational(int x, int y)
{
	struct rational z;
	z.x = x;
	z.y = y;
	return z;
}

//分数运算层
//递归化简
int gcd_rational(int a,int b)
{
    if (a%b) return gcd_rational(b,a%b);
    else return b;
}
//add
struct rational add_rational(struct rational z1, struct rational z2)
{
    int num_add = (num_part(z1))*(den_part(z2)) + (num_part(z2))*(den_part(z1));
    int den = den_part(z1)*den_part(z2);
    int gcd = gcd_rational(abs(num_add),den); //求最大公约数
	return make_rational(num_add/gcd,den/gcd);
}
//sub
struct rational sub_rational(struct rational z1, struct rational z2)
{
    int num_add = (num_part(z1))*(den_part(z2)) - (num_part(z2))*(den_part(z1));
    int den = den_part(z1)*den_part(z2);
    int gcd = gcd_rational(abs(num_add),den); //求最大公约数
	return make_rational(num_add/gcd,den/gcd);
}
//mul
struct rational mul_rational(struct rational z1, struct rational z2)
{
    int num_mul = num_part(z1)*num_part(z2);
    int den_mul = den_part(z1)*den_part(z2);
    int gcd = gcd_rational(abs(num_mul),den_mul); //求最大公约数
	return make_rational(num_mul/gcd,den_mul/gcd);
}
//div
struct rational div_rational(struct rational z1, struct rational z2)
{
	int num_div = num_part(z1)*den_part(z2);
    int den_div = den_part(z1)*num_part(z2);
    //符号设置
    if(num_div<0 && den_div<0) 
    {
        num_div = -num_div;
        den_div = -den_div;
    }
    else if (den_div<0) //符号移动至分子
    {
        num_div = -num_div;
        den_div = -den_div;
    }
    int gcd = gcd_rational(abs(num_div),den_div); //求最大公约数
	return make_rational(num_div/gcd,den_div/gcd);
}
//分数打印
void print_rational(struct rational z)
{   
    printf("%d/%d\n",num_part(z),den_part(z));
}

int main(void)
{
    struct rational a = make_rational(1, 8);  //a=1/8 
	struct rational b = make_rational(-1, 8);  //b=-1/8 
	print_rational(add_rational(a, b));
	print_rational(sub_rational(a, b));
	print_rational(mul_rational(a, b));
	print_rational(div_rational(a, b));

	return 0;
}

//添加enum枚举成员变量作为构造函数类型选择控制变量
// 提供复数存储表示层
//复数变量类型
enum coordinate_type { RECTANGULAR, POLAR };
struct complex_struct {
	enum coordinate_type t;
	double a, b;
};
//复数直角坐标提取
double real_part(struct complex_struct z)
{
	return z.a;
}
double img_part(struct complex_struct z)
{
	return z.b;
}
//复数极坐标提取
double magnitude(struct complex_struct z)
{
	return sqrt(z.a * z.a + z.b * z.b);
}
double angle(struct complex_struct z)
{
	return atan2(z.a, z.a);
}
//复数构造
struct complex_struct make_from_real_img(double x, double y)
{
	struct complex_struct z;
	z.t = RECTANGULAR;
	z.a = x;
	z.b = y;
	return z;
}

struct complex_struct make_from_mag_ang(double r, double A)
{
	struct complex_struct z;
	z.t = POLAR;
	z.a = r;
	z.b = A;
	return z;
}

/*
编译运行下面这段程序：
#include <stdio.h>

enum coordinate_type { RECTANGULAR = 1, POLAR };

int main(void)
{
	int RECTANGULAR;
	printf("%d %d\n", RECTANGULAR, POLAR);
	return 0;
}
结果是什么？并解释一下为什么是这样的结果。
运行结果打印0 2 ，因为枚举的成员变量名却和变量名在同一命名空间中，
所以会出现命名冲突，将int RECTANGULAR作为最新变量打印0而不是1.
*/
