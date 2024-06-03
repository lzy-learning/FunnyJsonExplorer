#pragma once

#include "JsonExplorerFactory.h"
#include "Style/TreeStyleFactory.h"
#include "Style/RectangleStyleFactory.h"

/**
 * 建造者模式：封装了构建JsonExplorerFactory所需步骤的抽象类
 */
class Builder
{
protected:
    std::shared_ptr<JsonExplorerFactory> mJsonExplorerFactory;

public:
    // 构造析构，构造函数中初始化mJsonExplorerFactory
    Builder();
    virtual ~Builder();

    /**
     * @description: 注册所有的图标族
     * @param {string&} iconFamilyFilename 图标族配置文件路径
     * @return {*}
     */
    virtual void registerIconFamily() = 0;

    /**
     * @description: 注册风格，需要程序员在扩展时在该函数中添加代码
     * @return {*}
     */
    virtual void registerStyle() = 0;

    virtual std::shared_ptr<JsonExplorerFactory> getFactory();
};

/**
 * 建造者模式：具体的建造者，扫描根目录下的ini文件中的图标族，registerStyle中注册矩形和树形两种风格
 */
class DefaultBuilder : public Builder
{
public:
    DefaultBuilder();
    virtual ~DefaultBuilder();

    /**
     * @description: 注册所有的图标族
     * @param {string&} iconFamilyFilename 图标族配置文件路径
     * @return {*}
     */
    virtual void registerIconFamily();

    /**
     * @description: 注册风格，需要程序员在扩展时在该函数中添加注册代码
     * @return {*}
     */
    virtual void registerStyle();
};

/**
 * 建造者模式：负责创建复杂对象JsonExplorerFactory
 * 事实上这个对象也没多复杂，不过为了可扩展性还是使用了建造者模式
 */
class Director
{
public:
    // 构造析构
    Director();
    ~Director();

    /**
     * @description: 根据传入的builder构造JsonExplorerFactory，并用智能指针的形式返回
     * @param {shared_ptr<Builder>} factoryBuilder
     * @return {*}
     */
    void makeDefaultJsonExplorerFactory(std::shared_ptr<Builder> factoryBuilder);
};