# FunnyJsonExplorer

### 编译
```shell
git clone https://github.com/lzy-learning/FunnyJsonExplorer.git

cd FunnyJsonExplorer/build
cmake ..
make
```

### 运行
```shell
cd ..
./fje -h

./fje -f test.json -s rect -i pocker-face
```

### 文件介绍
1. `build`：存放cmake生成的中间文件
2. `include`：头文件所在文件夹
    1. `JsonParser`：解析Json文件、获取Json根节点
    2. `Style`：特定风格抽象类及其实现
    3. `Utils`：一些工具类，比如可以用于保存Unicode的UString类
3. `src`：源文件所在文件夹
4. `icon-family.ini`：图标配置文件
5. `FJESofewareEngineeringProject.eddx`：项目UML图，用 亿图图示 打开
6. `test.json`：测试用的json文件