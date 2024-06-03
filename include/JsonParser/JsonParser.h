#pragma once

#include "Component.h"
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <map>
#include <vector>
#include <memory>
#include <stack>

/**
 * 枚举TOKEN的类型，一个简单的Json文件通常包含：
 *  1.英文冒号，用于指定键值
 *  2.字符串，被英文双引号包裹
 *  3.纯数字
 *  4.英文逗号，用于分隔不同单元
 *  5.空类型，null
 *  6.开闭大括号，用于引出一个Container
 */
enum TOKEN_TYPE
{
    COLON,
    STRING,
    NUMBER,
    COMMA,
    NULL_TYPE,
    OPEN_BRACE,
    CLOSE_BRACE,
};

/**
 * Token结构体
 * 解析Json文件时返回逐个Token以构建一个有限状态机
 */
struct Token
{
    TOKEN_TYPE type;
    std::string val;
};

/**
 * Tokenizer类
 * 提供getToken接口逐个返回Json文件中的Token，用于JsonParser类中的解析过程
 */
class Tokenizer
{
private:
    /**
     * @description: 从fstream文件流中读取一个字符，忽略空格和换行。如果已经读到文件末尾，返回空格' '
     * @return {char} 提取到的字符
     */
    char mGetCharacter();

public:
    /**
     * @description: 构造Tokenizer时必须指定合法的Json文件路径
     * @param {string} &fileName: 合法文件路径
     * @return
     */
    Tokenizer(const std::string &fileName);

    /**
     * @description: 判断是否还有Token
     * @return ture or false
     */
    bool hasNextToken();

    /**
     * @description: 每次调用返回一个Token并将文件指针移到下一个Token，不存在则抛出异常
     * @return Token
     */
    Token getToken();

    /**
     * @description: 重新打开一个文件流
     * @param {string} &fileName 文件路径
     * @return {*}
     */
    void reOpen(const std::string &fileName);

private:
    std::fstream mFile;
    size_t mPrevPos;
};

/**
 * Json解析器，使用单例模式，因为解析器不需要多个实现
 */
class JsonParser
{
private:
    // 文件流
    std::fstream mFile;

    // 根节点，这里没必要使用std::shared_ptr<Component>，因为Json文件一定是被一个{}包裹的，也就是一个Container
    std::shared_ptr<Container> mRoot;

    // 用一个栈结构保存在解析过程中的树结构，在遇到 { 的时候生成Container并入栈，在遇到 } 的时候出栈
    std::stack<std::shared_ptr<Container>> mParseStack;

    // 读取Token的对象
    Tokenizer mTokenizer;

    // 用智能指针+静态变量的方式实现的饿汉单例
    static std::shared_ptr<JsonParser> jsonParser;

    // 构造函数私有化
    JsonParser(const std::string &filename);
public:
    /**
     * 饿汉单例模式，只有在该函数调用的时候才会创建实例，且由于是静态变量，所以只会初始化一次
     */
    static std::shared_ptr<JsonParser> getInstance(const std::string &filename);

    /**
     * @description: 解析Json文件，解析失败会在内部处理异常并输出
     * @return
     */
    void parse();

    /**
     * @description: 返回Json树的根节点的指针
     * @return
     */
    std::shared_ptr<Container> getRoot();

    /**
     * @description: 重新打开一个Json文件进行解析
     * @param {string&} filename
     * @return {*}
     */
    void reOpen(const std::string &filename);
};
