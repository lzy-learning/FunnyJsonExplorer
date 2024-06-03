#pragma once

#include "AbstractStyleFactory.h"
#include "JsonParser/Component.h"
#include "JsonParser/JsonParser.h"
#include "Utils/UString.h"

/**
 * 矩形风格
 */
class RectangleStyleFactory : public AbstractStyleFactory
{
public:
    // 构造析构
    RectangleStyleFactory(const std::pair<std::string, std::string> &iconFamily) : AbstractStyleFactory(iconFamily) {}
    virtual ~RectangleStyleFactory() {}

    /**
     * @description: 创建方法
     * @param {pair<std::string, std::string>&} 图标族
     * @return {*}
     */
    static std::shared_ptr<AbstractStyleFactory> Create(const std::pair<std::string, std::string> &iconFamily);


    /**
     * 矩形风格的渲染函数，渲染原理和树形的差不多，都是从一个没有名称的Contianer，也就是最外层开始，
     * 逐层向内递归渲染，渲染完成之后替换一些
     */
    virtual void render(const std::string &filename);

private:
    // 存储所有行
    std::vector<UString> mAllDisplays;

    /**
     * @description: 递归遍历所有组成单元，将它们按行存储为std::string形式
     * @param {shared_ptr<Component>} &component
     * @param {int} level
     * @return {*}
     */    
    void mDraw(std::shared_ptr<Component> &component, int level);
};