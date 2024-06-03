#include "Style/RectangleStyleFactory.h"

std::shared_ptr<AbstractStyleFactory> RectangleStyleFactory::Create(const std::pair<std::string, std::string> &iconFamily)
{
    return std::make_shared<RectangleStyleFactory>(iconFamily);
}

void RectangleStyleFactory::mDraw(std::shared_ptr<Component> &component, int level)
{
    UString display;
    for (int i = 0; i < level; i++)
        display.appendCh("│").appendCh(" ").appendCh(" ");
    display.appendCh("├").appendCh("─");

    if (std::dynamic_pointer_cast<Container>(component))
    {
        auto container = std::dynamic_pointer_cast<Container>(component);
        display.appendCh(mIconFamily.first).appendCh(" ");
        display += container->draw();
        mAllDisplays.push_back(display);

        std::vector<std::shared_ptr<Component>> &components =
            container->getComponents();
        int n = components.size();
        for (int i = 0; i < n; i++)
            mDraw(components[i], level + 1);
    }
    else
    {
        auto leaf = std::dynamic_pointer_cast<Leaf>(component);
        display.appendCh(mIconFamily.second).appendCh(" ");
        display += leaf->draw();
        mAllDisplays.push_back(display);
    }
}

void RectangleStyleFactory::render(const std::string &filename)
{
    auto parser = JsonParser::getInstance(filename);
    parser->parse();
    auto root = parser->getRoot();
    std::vector<std::shared_ptr<Component>> &components = root->getComponents();

    int n = components.size();
    for (int i = 0; i < n; i++)
        mDraw(components[i], 0);
    int numDisplay = mAllDisplays.size();
    // 关于矩形后面要补多少 - 取决于程序实现，这里选择 最长行居中 的方式
    // 找到最长的那一行，确定每行的长度，以此决定要在每行后面补多少 - 号
    int maxIdx = 0, maxLen = 0;
    for (int i = 0; i < numDisplay; i++)
    {
        if (mAllDisplays[i].length() > maxLen)
        {
            maxIdx = i;
            maxLen = mAllDisplays[i].length();
        }
    }
    const UString &maxDisplay = mAllDisplays[maxIdx];
    int wordPos = 0;

    while (!maxDisplay.isAlpha(wordPos))
        wordPos++;
    int eachLen = maxLen + wordPos;
    std::string topLeft = "┌", topRight = "┐", bottomLeft = "└",
                bottomRight = "┘";
    std::string leftClosedLine = "├", rightClosedLine = "┤";
    // 每行补 - 和 ┤ 以及换行
    for (int i = 0; i < numDisplay; i++)
    {
        while (mAllDisplays[i].length() < eachLen)
        {
            mAllDisplays[i].appendCh("─");
        }
        mAllDisplays[i].appendCh("┤").appendCh("\n");
    }
    UString &firstLine = mAllDisplays[0];
    UString &lastLine = mAllDisplays[numDisplay - 1];
    // 第一行和最后一行去掉矩形的两个突出的线
    firstLine.replaceCh(0, topLeft);
    firstLine.replaceCh(firstLine.length() - 2, topRight);
    lastLine.replaceCh(0, bottomLeft);
    lastLine.replaceCh(lastLine.length() - 2, bottomRight);

    // 替换最后一行的空格和 | 号为闭合线，即-----
    for (int i = 1; i < lastLine.length(); i++)
    {
        if (lastLine[i] == "├")
        {
            lastLine[i] = "┴";
            break;
        }
        else if (lastLine[i] == " ")
            lastLine[i] = "─";
    }
    for (int i = 0; i < numDisplay; i++)
        std::cout << mAllDisplays[i];
}