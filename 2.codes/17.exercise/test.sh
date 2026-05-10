
# 简单测试脚本 for ex17
PROG="./ex17"
DB="test.db"

# 清理旧数据库
rm -f "$DB"

echo "=== 简单测试开始 ==="

# 创建数据库 (10行, 64字节)
echo -n "创建数据库: "
if $PROG "$DB" c 10 64 > /dev/null; then
    echo "PASS"
else
    echo "FAIL"
fi

# 设置记录 id=1
echo -n "设置 id 1: "
if $PROG "$DB" s 1 Alice alice@example.com > /dev/null; then
    echo "PASS"
else
    echo "FAIL"
fi

# 获取 id=1
echo -n "获取 id 1: "
if $PROG "$DB" g 1 > /dev/null; then
    echo "PASS"
else
    echo "FAIL"
fi

# 列表（应包含 id 1）
echo -n "列表: "
if $PROG "$DB" l | grep -q "Alice"; then
    echo "PASS"
else
    echo "FAIL"
fi

# 8. 删除 id=1
echo -n "Test 8 - 删除 id 1: "
if $PROG "$DB" d 1 > /dev/null; then
    echo "PASS"
else
    echo "FAIL"
fi

# 9. 删除后获取应失败
echo -n "Test 9 - 删除后获取 id 1: "
if $PROG "$DB" g 1 > /dev/null 2>&1; then
    echo "FAIL"
else
    echo "PASS"
fi

echo "=== 测试结束 ==="
rm -f "$DB"