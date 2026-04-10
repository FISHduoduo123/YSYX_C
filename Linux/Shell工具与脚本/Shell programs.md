# 习题
## 阅读 man ls ，然后使用 ls 命令进行如下操作：
- 所有文件（包括隐藏文件）
- 文件打印以人类可以理解的格式输出 
- 文件以最近修改顺序排序
- 以彩色文本显示输出结果  
  
 ![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/Shell%E5%B7%A5%E5%85%B7%E4%B8%8E%E8%84%9A%E6%9C%AC/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-10%20184805.png)  
## 编写两个 bash 函数 marco 和 polo 执行下面的操作。 每当你执行 marco 时，当前的工作目录应当以某种形式保存，当执行 polo 时，无论现在处在什么目录下，都应当 cd 回到当时执行 marco 的目录。 为了方便 debug，你可以把代码写在单独的文件 marco.sh 中，并通过 source marco.sh 命令，（重新）加载函数。
![](https://github.com/FISHduoduo123/YSYX_C/blob/main/Linux/Shell%E5%B7%A5%E5%85%B7%E4%B8%8E%E8%84%9A%E6%9C%AC/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202026-04-10%20191002.png)  

## 假设您有一个命令，它很少出错。因此为了在出错时能够对其进行调试，需要花费大量的时间重现错误并捕获输出。 编写一段 bash 脚本，运行如下的脚本直到它出错，将它的标准输出和标准错误流记录到文件，并在最后输出所有内容。 加分项：报告脚本在失败前共运行了多少次。
```
 #!/usr/bin/env bash

 n=$(( RANDOM % 100 ))

 if [[ n -eq 42 ]]; then
    echo "Something went wrong"
    >&2 echo "The error was using magic numbers"
    exit 1
 fi

 echo "Everything went according to plan"
```
```
#!/usr/bin/env bash

# 定义日志文件
LOG_FILE="command_log.txt"
# 初始化运行计数器
count=0

# 清空日志文件
> "$LOG_FILE"

# 循环执行命令
while true; do
    # 执行命令，同时将 stdout 和 stderr 追加到日志文件
    if (( RANDOM % 100 != 42 )); then
        echo "Everything went according to plan" >> "$LOG_FILE" 2>&1
        ((count++))
    else
        echo "Something went wrong" >&2
        echo "The error was using magic numbers" >&2
        # 将错误信息也写入日志
        echo "Something went wrong" >> "$LOG_FILE" 2>&1
        echo "The error was using magic numbers" >> "$LOG_FILE" 2>&1
        ((count++))
        break
    fi
done

# 输出统计结果和完整日志
echo "命令在失败前共成功运行了 $((count - 1)) 次"
echo " 完整日志内容如下："
cat "$LOG_FILE"
```
## 本节课我们讲解的 find 命令中的 -exec 参数非常强大，它可以对我们查找的文件进行操作。但是，如果我们要对所有文件进行操作呢？例如创建一个 zip 压缩文件？我们已经知道，命令行可以从参数或标准输入接受输入。在用管道连接命令时，我们将标准输出和标准输入连接起来，但是有些命令，例如 tar 则需要从参数接受输入。这里我们可以使用 xargs 命令，它可以使用标准输入中的内容作为参数。 例如 ls | xargs rm 会删除当前目录中的所有文件。

#您的任务是编写一个命令，它可以递归地查找文件夹中所有的 HTML 文件，并将它们压缩成 zip 文件。注意，即使文件名中包含空格，您的命令也应该能够正确执行（提示：查看 xargs 的参数 -d，译注：MacOS 上的 xargs 没有 -d，查看这个 issue）

如果您使用的是 MacOS，请注意默认的 BSD find 与 GNU coreutils 中的是不一样的。你可以为 find 添加 -print0 选项，并为 xargs 添加 -0 选项。作为 Mac 用户，您需要注意 mac 系统自带的命令行工具和 GNU 中对应的工具是有区别的；如果你想使用 GNU 版本的工具，也可以使用 brew 来安装。  
```find . -type f -name "*.html" -print0 | xargs -0 zip -r html_files.zip```  

## （进阶）编写一个命令或脚本递归的查找文件夹中最近修改的文件。更通用的做法，你可以按照最近的修改时间列出文件吗？
```find . -type f -printf "%T+ %p\n" | sort -r | head -n 10```
