#include <iostream>
#include <string>
#include "Utils/Utility.h"
#include "JsonExplorerBuilder.h"

int main(int argc, char **argv)
{
    /**
     * 解析用户的命令行参数
     */
    std::string jsonFilename = "", styleName = "", iconFamily = "";
    parseParam(argc, argv, jsonFilename, styleName, iconFamily);
    // 必须指定文件名
    if (jsonFilename.empty())
    {
        std::cout << "Json file path must be specified!!" << std::endl;
        std::cout << std::endl;
        printUsage();
        exit(-1);
    }
    // styleName默认为Rectangle
    if (styleName.empty())
        styleName = "rect";
    // iconFamily默认为pocker-face
    if (iconFamily.empty())
        iconFamily = "poker-face";

    /**
     * 渲染Json文件
     */
    // 获取JsonExplorerFactory的Builder
    auto builder = std::make_shared<DefaultBuilder>();
    // 获取Director
    auto director = std::make_shared<Director>();

    // 构建jsonExplorerFactory
    director->makeDefaultJsonExplorerFactory(builder);
    // 获取jsonExplorerFactory
    auto jsonExplorerFactory = builder->getFactory();

    // 用户指定json文件、风格和图标族，然后进行渲染
    auto jsonExplorer = jsonExplorerFactory->Get(styleName, iconFamily);
    jsonExplorer->render(jsonFilename);

    return 0;
}