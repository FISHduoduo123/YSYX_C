#include "ex22.h"
#include "dbg.h"


/*
下面是一些编程C代码时需要遵循的规则，可以让你避免与栈相关的bug：

    不要隐藏某个变量，就像上面scope_demo中对count所做的一样。这可能会产生一些隐蔽的bug，你认为你改变了某个变量但实际上没有。
    避免过多的全局变量，尤其是跨越多个文件。如果必须的话，要使用读写器函数，就像get_age。这并不适用于常量，因为它们是只读的。我是说对于THE_SIZE这种变量，如果你希望别人能够修改它，就应该使用读写器函数。
    在你不清楚的情况下，应该把它放在堆上。不要依赖于栈的语义，或者指定区域，而是要直接使用malloc创建它。
    不要使用函数级的静态变量，就像update_ratio。它们并不有用，而且当你想要使你的代码运行在多线程环境时，会有很大的隐患。对于良好的全局变量，它们也非常难于寻找。
    避免复用函数参数，因为你搞不清楚仅仅想要复用它还是希望修改它的调用者版本。

*/
const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count)
{
    log_info("count is: %d", count);

    if(count > 10) {
        int count = 100;  // BAD! BUGS!

        log_info("count in this scope is %d", count);
    }

    log_info("count is at exit: %d", count);

    count = 3000;

    log_info("count after assign: %d", count);

    /*  
        编写一个递归调用并导致栈溢出的函数。
        如果不知道递归函数是什么的话，
        试着在scope_demo底部调用scope_demo本身，会形成一种循环。
    */
    scope_demo(count);
}

int main(int argc, char *argv[])
{
    // test out THE_AGE accessors
    log_info("My name: %s, age: %d", MY_NAME, get_age());

    set_age(100);

    log_info("My age is now: %d", get_age());

    // test out THE_SIZE extern
    log_info("THE_SIZE is: %d", THE_SIZE);
    print_size();

    THE_SIZE = 9;

    log_info("THE SIZE is now: %d", THE_SIZE);
    print_size();

    // test the ratio function static
    log_info("Ratio at first: %f", update_ratio(2.0));
    log_info("Ratio again: %f", update_ratio(10.0));
    log_info("Ratio once more: %f", update_ratio(300.0));

    // test the scope demo
    int count = 4;
    scope_demo(count);
    scope_demo(count * 20);

    log_info("count after calling scope_demo: %d", count);

    // 使用指针来访问原本不能访问的变量。
    //int *count_ptr = &THE_AGE;

    return 0;
}