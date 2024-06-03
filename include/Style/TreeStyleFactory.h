#pragma once

#include "AbstractStyleFactory.h"
#include "JsonParser/Component.h"
#include "JsonParser/JsonParser.h"
#include <unordered_map>

/**
 * 树形风格
 */
class TreeStyleFactory : public AbstractStyleFactory
{
public:
    // 构造析构
    TreeStyleFactory(const std::pair<std::string, std::string> &iconFamily) : AbstractStyleFactory(iconFamily) {}
    virtual ~TreeStyleFactory() {}

    /**
     * @description: 创建方法
     * @param {pair<std::string, std::string>&} 图标族
     * @return {*}
     */
    static std::shared_ptr<AbstractStyleFactory> Create(const std::pair<std::string, std::string> &iconFamily);

    /**
     * @description: 实现的渲染函数，就是从根节点开始递归遍历所有单元并打印
     * @param {string} &filename
     * @return {*}
     */
    virtual void render(const std::string &filename);

private:
    /**
     * @description:
     * @param {shared_ptr<Component>} &component
     * @param {int} level
     * @param {bool} isLast
     * @param {bool} isRootLast
     * 表示在顶层Container中是否是最后一个Component了，如果是则不需要再画
     * |，无论它的level是多少
     * @return {*}
     */
    void mDraw(std::shared_ptr<Component> &component, int level,
               bool isLast = false, bool isRootLast = false);
};