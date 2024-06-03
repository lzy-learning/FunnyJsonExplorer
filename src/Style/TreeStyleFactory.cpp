#include "Style/TreeStyleFactory.h"

std::shared_ptr<AbstractStyleFactory> TreeStyleFactory::Create(const std::pair<std::string, std::string> &iconFamily)
{
    return std::make_shared<TreeStyleFactory>(iconFamily);
}

void TreeStyleFactory::render(const std::string &filename)
{
    auto parser = JsonParser::getInstance(filename);
    parser->parse();
    auto root = parser->getRoot();
    std::vector<std::shared_ptr<Component>> &components = root->getComponents();
    int n = components.size();
    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
            mDraw(components[i], 0, true, true);
        else
            mDraw(components[i], 0, false, false);
    }
}

void TreeStyleFactory::mDraw(std::shared_ptr<Component> &component, int level,
                             bool isLast, bool isRootLast)
{
    if (std::dynamic_pointer_cast<Container>(component))
    {
        auto container = std::dynamic_pointer_cast<Container>(component);
        std::string display = "";
        if (level == 0)
        {
            if (isLast)
                display += "└─";
            else
                display += "├─";
        }
        else
        {
            if (!isRootLast)
                display += "│";
            else
                display += " ";
            for (int i = 0; i < level; i++)
                display += "  ";
            if (isLast)
                display += "└─";
            else
                display += "├─";
        }
        display += mIconFamily.first;
        display += " ";
        display += container->draw();
        display += "\n";
        std::cout << display;
        std::vector<std::shared_ptr<Component>> &components =
            container->getComponents();
        int n = components.size();
        for (int i = 0; i < n; i++)
            mDraw(components[i], level + 1, i == n - 1 ? true : false, isRootLast);
    }
    else
    {
        auto leaf = std::dynamic_pointer_cast<Leaf>(component);
        std::string display = "";
        if (level == 0)
        {
            if (isLast)
                display += "└";
            else
                display += "├─";
        }
        else
        {
            if (!isRootLast)
                display += "│";
            else
                display += " ";
            for (int i = 0; i < level; i++)
                display += "  ";
            if (isLast)
                display += "└─";
            else
                display += "├─";
        }

        display += mIconFamily.second;
        display += " ";
        display += leaf->draw();
        display += "\n";
        std::cout << display;
    }
}
