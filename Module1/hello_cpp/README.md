# Random Word Selector - Google Test 示例

这是一个使用 Google Test 测试框架的 C++ 水库采样算法实现。

## 文件结构

```
hello_cpp/
├── src/                         # 未来可选的源码目录
├── test/                        # 测试文件目录
│   ├── simple_test.cpp         # 自实现的轻量级测试框架
│   ├── test_random_word.cpp    # Google Test版本测试套件
│   └── README.md               # 测试说明文档
├── RandomWordSelector.h        # 头文件
├── RandomWordSelector.cpp      # 实现文件
├── RandomWorld.cpp            # 主程序
├── CMakeLists.txt             # CMake 构建配置
├── build_and_test.sh          # 构建和测试脚本
└── README.md                  # 本文件
```

## 构建和运行

### 方法1: 使用构建脚本（推荐）

```bash
./build_and_test.sh
```

### 方法2: 手动构建

```bash
mkdir build && cd build
cmake ..
make
./RandomWordTests  # 运行测试
```

## 测试内容

测试文件位于 `test/` 目录中，包含以下测试用例：

1. **空输入测试** - 验证空输入时的行为
2. **单个单词测试** - 确保单个单词被正确选择
3. **多个单词测试** - 验证结果是输入单词之一
4. **分布均匀性测试** - 统计测试验证随机性
5. **确定性测试** - 相同种子产生相同结果
6. **大数据集测试** - 测试算法处理大量数据的能力
7. **边界情况测试** - 测试两个单词的情况
8. **性能测试** - 验证算法的执行效率

## 运行主程序

```bash
# 构建后，可以这样运行主程序：
echo "apple banana cherry date" | ./build/RandomWorld

# 或者从文件读取：
./build/RandomWorld < input.txt
```

## Google Test 特性演示

- ✅ 基本断言 (`EXPECT_EQ`, `EXPECT_TRUE`, `EXPECT_FALSE`)
- ✅ 测试固件 (`TEST_F`)
- ✅ 参数化测试概念
- ✅ 性能测试
- ✅ 统计测试
- ✅ 边界条件测试

## 依赖项

- C++20 兼容的编译器
- CMake 3.20+
- Google Test (自动下载如果未安装)

## 算法说明

实现了 Knuth 的水库采样算法：
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 每个元素被选中的概率相等：1/n
