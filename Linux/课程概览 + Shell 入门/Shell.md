### cd-change directory，切换目录
给它传入一个路径，该路径就会成为你的当前工作目录，提示符也会随之变化。
```
missing:~$ cd /bin
missing:/bin$ cd /
missing:/$ cd ~
missing:~$
```
许多命令在未指定路径时，默认作用于当前工作目录。如果不确定自己在哪个目录，**可以运行 pwd（print working directory，打印当前工作目录）**，或者查看 $PWD 环境变量（如 echo $PWD）。    
当前工作目录的另一重要作用是让我们能够使用相对路径。到目前为止我们看到的都是绝对路径：以 / 开头，给出了从文件系统根目录到目标位置的完整路径。 实际使用中，相对路径更常用。之所以叫「相对」，是因为它们是相对于当前工作目录来解析的。对于相对路径（即任何不以 / 开头的路径），Shell 会先在当前工作目录中查找路径的第一部分，然后逐级向下查找。例如：
```
missing:~$ cd /
missing:/$ cd bin
missing:/bin$
```  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-09%20181403.png)  
每个目录里还都有两个「特殊路径」：. 和 .. 。 其中，. 表示「当前目录」，.. 表示「父目录」。例如：
```
missing:~$ cd /
missing:/$ cd bin/../bin/../bin/././../bin/..
missing:/$
```
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-09%20182916.png)  
### 其余命令
在大多数计算机上，这会列出非常多的程序，但我们只关注其中最重要的几个。先从简单的开始：
- ```cat hello.txt```：打印 hello.txt 的全部内容
- ```sort hello.txt```：将 hello.txt 的各行按字典序排序后输出
- ```uniq hello.txt```：去除 hello.txt 中连续重复的行
- ```head hello.txt``` 和 ```tail hello.txt```：分别打印 hello.txt 的前几行和后几行
还有 ```grep pattern hello.txt```，它会在指定文本文件中查找所有匹配 pattern 的行。
这里的 pattern 实际上是正则表达式（regular expression），可以描述非常复杂的匹配模式  
除了指定单个文件，你也可以指定一个目录作为搜索范围（或者直接不写，默认就是当前目录 . ），并加上 -r 参数让 grep 递归搜索目录里的所有文本文件，输出匹配的行。  
  
还有一些实用工具，使用方式稍微复杂一些。先看 sed——一个可编程的文件编辑器。它有自己的「小语言」，可以自动化地修改文件。最常见的用法是：
- ```missing:~$ sed -i 's/pattern/replacement/g' hello.txt```
这条命令会把 hello.txt 中所有的 pattern 替换为 replacement 。具体来说：
- -i 参数表示直接修改文件（inline），而不是只在终端输出替换后的内容
- s/ 是 sed 语法里表示「替换」的意思
- 两个 / 用来分隔「匹配模式」和「替换内容」
- 结尾的 /g 表示在每一行中替换所有匹配项，而不仅仅是第一个
和 grep 一样，这里的 pattern 也是正则表达式，可以描述非常复杂的匹配模式。此外，正则表达式替换还允许 replacement 引用匹配模式中的部分内容，我们稍后会通过例子演示这一点。
**find**
它可以递归地查找满足特定条件的文件。比如：
- ```missing:~$ find ~/Downloads -type f -name "*.zip" -mtime +30```
这会在下载（Downloads）目录中查找所有超过 30 天的 ZIP 文件。
- ```missing:~$ find ~ -type f -size +100M -exec ls -lh {} \;```
这会在 home 目录中查找所有大于 100M 的文件并列出它们。注意，-exec 接受一条命令，命令以 ; 结尾（因此需要像转义空格那样对它转义）。find 会把每个匹配文件的路径替换到 {} 的位置。
- ```missing:~$ find . -name "*.py" -exec grep -l "TODO" {} \;```
这会在当前工作目录下查找所有包含 TODO （这个大写单词）的 .py 文件。

# 练习 
本课程要求你使用类 Unix 的 Shell，如 Bash 或 ZSH 。若你在 Linux 或 macOS 上，无需额外设置。若你在 Windows 上，请确认你用的不是 cmd.exe 或 PowerShell；你可以使用 Windows Subsystem for Linux 或 Linux 虚拟机来获得 Unix 风格的命令行工具。要确认当前 Shell 是否合适，可运行 echo $SHELL；若输出类似 /bin/bash 或 /usr/bin/zsh ，就说明没问题。  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-09%20193040.png)  

## ls 的 -l 选项（flag）作用是什么？运行 ls -l / 并观察输出。每一行最前面的 10 个字符分别代表什么？（提示：man ls）
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-10%20092511.png)  
-l: 用于详细显示文件信息的选项从(权限,链接数,所属用户所属组,文件大小,修改时间,
文件名)  
## 在命令 find ~/Downloads -type f -name "*.zip" -mtime +30 中，*.zip 是一个 「glob」。什么是 glob ？新建一个测试目录并创建一些文件，试试 ls *.txt 、ls file?.txt 、ls {a,b,c}.txt 等模式。参见 Bash 手册中的 Pattern Matching 。
  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-10%20094909.png)    
**glob**作为文件名通配符，作为批量匹配文件名的规则。  
- ```ls *.txt```  
- ```ls file?.txt```  
- ```ls {a,b,c}.txt```    
先创建三个文件  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-10%20095137.png)     
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-10%20100031.png)     
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-10%20100044.png)   

## '单引号'、"双引号" 和 $'ANSI 引号' 有什么区别？写一条命令，输出一个同时包含字面量 $ 、! 和换行符的字符串。参见 Quoting 。
### 单引号 ' '
- 1.不解析引号内字符串  
- 2.变量  $ 、通配符  * 、转义全都失效  
### 双引号 " "
- 解析变量 $，但* {} ?不解析通配符   
### $' '    
- 1.专门解析 转义字符： \n 换行、 \t 制表符  
- 2.不解析变量、通配符    
## Shell 有三条标准流：stdin（0）、stdout（1）、stderr（2）。运行 ls /nonexistent /tmp ，把 stdout 和 stderr 分别重定向到两个文件。你将如何把两者都重定向到同一个文件？参见 Redirections 。
创建一个a.sh
```
内容如下:
ls -l /
lsl 
```
将正确输出与错误输出重定向至同一个文件内
```./a.sh > a.txt 2>&1```
## $? 保存上一条命令的退出状态（0 表示成功）。&& 仅在前一条成功时执行后一条；|| 仅在前一条失败时执行后一条。写一个一行命令：仅当 /tmp/mydir 不存在时才创建它。参见 Exit Status 。
```mdkir -p /tmp/mydir```
## 为什么 cd 必须是 Shell 内建命令，而不能是独立程序？（提示：想想子进程能影响和不能影响父进程的哪些状态。）
如果作为独立的程序运行时将会创建一基于目标路径的的子程序，但无法实现修改父进程的工作目录的效果，内建命令可直接在 Shell 自身进程中执行，从而改变 Shell 的当前工作目录
## 写一个脚本，接收文件名参数（$1），用 test -f 或 [ -f ... ] 检查该文件是否存在，并根据结果输出不同提示。参见 Bash Conditional Expressions 。
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-10%20111430.png)  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-10%20111421.png)  
## 把上一题完成的脚本保存为文件（如 check.sh）。先运行 ./check.sh somefile ，会发生什么？然后执行 chmod +x check.sh 再试一次。为什么这一步是必须的？（提示：比较 chmod 前后的 ls -l check.sh 输出）
**默认创建文件不具有系统可执行权限**
通过```chmod +x [文件路径]```添加权限  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-10%20111809.png)  
## 在脚本的 set 选项（flag）里加入 -x 会发生什么？写个简单脚本试试并观察输出。参见 The Set Builtin 。
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-10%20113243.png)  
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/%E8%AF%BE%E7%A8%8B%E6%A6%82%E8%A7%88%20%2B%20Shell%20%E5%85%A5%E9%97%A8/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-10%20113233.png)
## 写一条命令，把文件复制为带当天日期的备份文件名（例如 notes.txt → notes_2026-01-12.txt）。（提示：$(date +%Y-%m-%d)）参见 Command Substitution 。

## 修改讲义中的「复现偶尔才会失败的测试」脚本（flaky test），使它能够从命令行参数接收测试命令，而不是在脚本中写死 cargo test my_test。（提示：$1 或 $@）参见 Special Parameters 。

## 使用管道找出你「home 目录」中最常见的 5 种文件扩展名。（提示：组合 find 、grep / sed / awk、sort、uniq -c 以及 head）

## xargs 会把 stdin 的每一行转换为命令参数。结合 find 和 xargs（不要用 find -exec），找出目录中所有 .sh 文件，并用 wc -l 统计每个文件行数。加分项：正确处理文件名中的空格。（提示：-print0 和 -0）参见 man xargs 。

## 使用 curl 获取 课程网站 的 HTML，并通过 grep 统计列出了多少讲。（提示：找出每讲课程名称在那份 HTML 中的共性；用 curl -s 关闭进度输出。）

## jq 是处理 JSON 的强大工具。用 curl 获取示例数据 https://microsoftedge.github.io/Demos/json-dummy-data/64KB.json，再用 jq 提取 version 大于 6 的人员姓名。（提示：先 jq . 看结构；再试 jq '.[] | select(...) | .name'）

## awk 可以按列值过滤行并改写输出。例如，awk '$3 ~ /pattern/ {$4=""; print}' 会只输出第三列匹配 pattern 的行，并省略第四列。请写一个 awk 命令：只输出第二列大于 100 的行，并交换第一列和第三列。可用这条命令测试：printf 'a 50 x\nb 150 y\nc 200 z\n'

## 拆解讲义中的 SSH 日志处理管道：每一步分别做了什么？然后仿照它构建一个管道，从 ~/.bash_history（或 ~/.zsh_history）中找出你最常使用的 Shell 命令。

