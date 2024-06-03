#pragma once

#include <iostream>
#include <string>
#include <utility>

/**
 * 抽象工厂：所有Json可视化风格都必须继承该类并重写render方法
 */
class AbstractStyleFactory
{
protected:
    std::pair<std::string, std::string> mIconFamily;

public:
    AbstractStyleFactory(const std::pair<std::string, std::string> &iconFamily) : mIconFamily(iconFamily) {}
    virtual ~AbstractStyleFactory() {}

    /**
     * @description: 渲染函数，默认支持传入Json文件路径，也可在子类中添加其他重载
     * @return {*}
     */
    virtual void render(const std::string &filename) = 0;
};