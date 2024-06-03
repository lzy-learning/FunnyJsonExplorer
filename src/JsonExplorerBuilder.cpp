#include "JsonExplorerBuilder.h"

Builder::Builder()
{
    mJsonExplorerFactory = std::make_shared<JsonExplorerFactory>();
}
Builder::~Builder() {}

std::shared_ptr<JsonExplorerFactory> Builder::getFactory()
{
    return mJsonExplorerFactory;
}

Director::Director() {}
Director::~Director() {}

void Director::makeDefaultJsonExplorerFactory(std::shared_ptr<Builder> factoryBuilder)
{
    // 注册图标族
    factoryBuilder->registerIconFamily();
    // 注册具体风格
    factoryBuilder->registerStyle();
}

DefaultBuilder::DefaultBuilder() {}
DefaultBuilder::~DefaultBuilder() {}

void DefaultBuilder::registerIconFamily()
{
    std::string iconFamilyFilename = "icon-family.ini";
    auto iconFamilies = readIconFamily(iconFamilyFilename);
    for (auto it = iconFamilies.begin(); it != iconFamilies.end(); it++)
        mJsonExplorerFactory->registry(it->first, it->second.first, it->second.second);
}

void DefaultBuilder::registerStyle()
{
    (*mJsonExplorerFactory).registry("tree", TreeStyleFactory::Create).registry("rect", RectangleStyleFactory::Create);
}