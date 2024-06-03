#include "JsonExplorerFactory.h"

JsonExplorerFactory &JsonExplorerFactory::registry(const std::string &name, const std::string &containerIcon,
                                                   const std::string &leafIcon)
{
    if (mIconFamilies.find(name) != mIconFamilies.end())
    {
        std::cout
            << "Register icon family " << name
            << " failed: Duplicate name, please check the configuration file!"
            << std::endl;
    }
    else
        mIconFamilies[name] = std::make_pair(containerIcon, leafIcon);
    return *this;
}

JsonExplorerFactory &JsonExplorerFactory::registry(const std::string &name, CreateFunc createFunc)
{
    if (mStyleFactory.find(name) != mStyleFactory.end())
    {
        std::cout
            << "Register style factory " << name
            << " failed: Duplicate name!"
            << std::endl;
    }
    else
        mStyleFactory[name] = createFunc;
    return *this;
}

std::shared_ptr<AbstractStyleFactory> JsonExplorerFactory::Get(
    const std::string &styleName, const std::string &iconFamilyName)
{
    if (mStyleFactory.find(styleName) == mStyleFactory.end())
    {
        std::cout << "Unregistered style: " << styleName << std::endl;
        return nullptr;
    }
    // 根据风格名称获取对应的风格类
    auto styleFactory = mStyleFactory[styleName];

    // 如果指定的图标族存在则创建带有指定图标族的explorer，否则图标族为空字符串
    if (mIconFamilies.find(iconFamilyName) == mIconFamilies.end())
    {
        std::cout << "Unregistered icon family: " << iconFamilyName << std::endl;
        return styleFactory({"", ""});
    }
    return styleFactory(mIconFamilies[iconFamilyName]);
}