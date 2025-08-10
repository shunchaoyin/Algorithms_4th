#!/bin/bash

# 构建和测试脚本
set -e

echo "=== Random Word Project Build Script ==="

# 创建构建目录
mkdir -p build
cd build

# 运行CMake配置
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Debug

# 构建项目
echo "Building project..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# 运行测试
echo "Running tests..."
./SimpleTests

echo "=== Build and Test Complete ==="

# 提供使用说明
echo ""
echo "To run the main program:"
echo "  echo 'apple banana cherry' | ./RandomWorld"
echo ""
echo "To run tests again:"
echo "  ./SimpleTests"
