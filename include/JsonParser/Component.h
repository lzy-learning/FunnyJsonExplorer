#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <map>
#include <exception>

/**
 * 组合模式中的单元抽象类，包含每个结点的共有属性和方法，比如名称
 */
class Component
{
protected:
    std::string mKey;

public:
    Component();
    Component(const std::string &key);
    virtual std::string draw() = 0;
    virtual ~Component();
};

/**
 * 组合模式中的叶子结点类，目前支持字符串、整形、浮点型和null类型
 */
class Leaf : public Component
{
private:
    // 节点值用string存储，在需要使用的时候再根据mType强转
    std::string mVal;

public:
    // 构造析构
    Leaf();
    Leaf(const std::string &key);
    Leaf(const std::string &key, const std::string &value);
    virtual ~Leaf();

    /**
     * @description: 获取当前结点的值
     * @return {std::string}
     */
    std::string getStrValue();

    /**
     * @description: 设置当前叶节点的值
     * @param {string} &value
     * @return {*}
     */
    void setValue(const std::string &value);

    /**
     * @description: 获取当前结点的键
     * @return {std::string}
     */
    std::string getKey();

    /**
     * @description: 设置当前结点的键
     * @param {string} &key
     * @return {*}
     */
    void setKey(const std::string &key);

    /**
     * @description: draw函数负责返回当前结点的键和值的组合，如果值为空则只返回键
     * @return {std::string}
     */
    virtual std::string draw();
};

/**
 * 这里就是组合模式的核心所在，通过一个Container和多态机制将结点组织成一个树的形式
 * Container中通过一个std::vector存储它的子节点
 */
class Container : public Component
{
private:
    std::vector<std::shared_ptr<Component>> mInnerComponents;

public:
    /**
     * 构造析构
     */
    Container();
    Container(const std::string &key);
    virtual ~Container();

    /**
     * @description: 设置键的名称
     * @param {string} &key
     * @return {*}
     */
    void setName(const std::string &key);

    /**
     * @description: 添加新的组件
     * @param {shared_ptr<Component>} component 组件的智能指针，多态形式，可以传入Container或Leaf
     * @return {*}
     */
    void addComponent(std::shared_ptr<Component> component);

    /**
     * @description: 获取容器内所有的Component
     * @return {std::vector<std::shared_ptr<Component>>} vector数组
     */
    std::vector<std::shared_ptr<Component>> &getComponents();

    /**
     * @description: draw函数只返回自己的键名称
     * @return {std::string}
     */
    virtual std::string draw();
};