## Write a "Hello World" program under GNU/Linux
Write a "Hello World" program, compile it, then run it under GNU/Linux. If you do not know what to do, refer to the GNU/Linux tutorial above.  
### 编写Hello World 
**c创建文件**  
```touch code.c```  
创建完成后编写打印程序。  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/gdb_test/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-08%20173826.png)    
## Write a Makefile to compile the "Hello World" program
Write a Makefile to compile the "Hello World" program above. If you do not know what to do, refer to the GNU/Linux tutorial above.    
**创建Makefile文件**    
```touch Makefile```    
**编写编译脚本**    
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/gdb_test/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-08%20174228.png)  
**运行Makefile完成编译**    
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/gdb_test/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-08%20174446.png)    
**运行可执行程序**    
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/gdb_test/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-08%20175316.png)   
## Learn to use GDB
Read the GDB tutorial above and use GDB following the tutorial. In PA1, you will be required to implement a simplified version of GDB. If you have not used GDB, you may have no idea to finish PA1.  
### GDB测试命令
#### 启动
- gdb ./prog：加载可执行文件
**打开调试hello可执行程序**  
```gdb hello```  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/gdb_test/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-08%20174928.png)  
#### 查看源代码
- list [N|func] / l：查看源码  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/gdb_test/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-08%20180117.png)  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/gdb_test/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-08%20181459.png)   
#### 设置断点并运行
- break N / b N：在第 N 行设置断点  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/gdb_test/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-08%20182339.png)    
- run / r：开始运行程序  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/gdb_test/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-08%20182451.png)    
- print var / p var：打印变量值  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/gdb_test/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-08%20182515.png)   
- delete N：删除编号为 N 的断点  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/gdb_test/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-08%20182612.png)  
- continue / c：继续执行到下一个断点  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/gdb_test/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-08%20182630.png) 
#### 退出
- quit 或 q：退出调试器  
### 其他命令
- next / n：单步执行（不进入函数）
- step / s：单步执行（进入函数）
- break func：在函数入口设置断点
- info breakpoints：查看断点列表
- set var x=10：修改变量值
- ptype var：查看变量类型
- ···
