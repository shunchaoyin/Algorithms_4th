# 测试目录

本目录包含随机单词选择器的所有测试文件。

## 文件说明

- `simple_test.cpp` - 自实现的轻量级测试框架，不依赖外部库
- `test_random_word.cpp` - Google Test版本的完整测试套件

## 运行测试

### 简单测试（推荐）
```bash
# 从项目根目录运行
./build_and_test.sh

# 或者手动构建和运行
mkdir build && cd build
cmake ..
make
./SimpleTests
```

### Google Test（需要网络连接）
如果你想使用Google Test版本，需要：

1. 取消注释 `../CMakeLists.txt` 中的Google Test部分
2. 确保网络连接正常
3. 重新构建项目

```bash
cd build
cmake ..
make
./GoogleTests
```

## 测试覆盖

✅ 空输入处理  
✅ 单个单词选择  
✅ 多个单词随机选择  
✅ 确定性行为（相同种子相同结果）  
✅ 分布均匀性验证  
✅ 大数据集处理  
✅ 性能测试  
