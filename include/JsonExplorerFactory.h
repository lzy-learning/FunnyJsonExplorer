#pragma once

#include <unordered_map>
#include <memory>
#include "Utils/Utility.h"
#include "Style/AbstractStyleFactory.h"

// 实体类提供的创建对象的Create方法，体现为函数指针
typedef std::shared_ptr<AbstractStyleFactory> (*CreateFunc)(const std::pair<std::string, std::string> &);

/**
 * 工厂方法：封装了new对象的方法，用户调用Create函数并传入需要的风格名称和图标族名称，返回对应的AbstractStyleFactory
 */
class JsonExplorerFactory
{
public:
  // 构造析构函数
  JsonExplorerFactory() = default;
  ~JsonExplorerFactory() = default;

  /**
   * @description: 注册图标族
   * @param {string&} name 图标族名称
   * @param {string&} containerIcon 容器结点的图标
   * @param {string&} leafIcon 叶子节点的图标
   * @return {JsonExplorerFactory&} 返回自身，支持链式调用
   */
  JsonExplorerFactory &registry(const std::string &name, const std::string &containerIcon,
                                const std::string &leafIcon);

  /**
   * @description: 注册风格
   * @param {string} &name 风格名称
   * @param {CreateFunc} createFunc 风格类提供的Create函数
   * @return {JsonExplorerFactory&} 返回自身，支持链式调用
   */
  JsonExplorerFactory &registry(const std::string &name, CreateFunc createFunc);

  /**
   * @description:工厂方法，指定风格名称和图标族，创建一个具体产品(有特定风格和图标族的)并返回
   * @param {string&} styleName
   * @param {string&} iconFamilyName
   * @return {*}
   */
  std::shared_ptr<AbstractStyleFactory> Get(
      const std::string &styleName, const std::string &iconFamilyName);
      
private:
  // 保存名称到图标族的映射
  std::unordered_map<std::string, std::pair<std::string, std::string>>
      mIconFamilies;
  // 保存名称到风格工厂的Create方法的映射
  std::unordered_map<std::string, CreateFunc> mStyleFactory;
};
