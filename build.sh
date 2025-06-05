#!/bin/bash
###
 # @Descripttion: 
 # @Author: xujg
 # @version: 
 # @Date: 2025-06-05 11:45:38
 # @LastEditTime: 2025-06-05 13:05:17
### 

set -e  # 出错时终止脚本

echo "📂 创建 build 目录..."
rm -rf build
mkdir -p build
cd build

echo "⚙️ 运行 CMake..."
cmake ..

echo "🔨 编译项目..."
make -j$(nproc)
cp ../config.yaml .
echo "✅ 编译完成，执行文件已生成在 ./build/ 目录下"
