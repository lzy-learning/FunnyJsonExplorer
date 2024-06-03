#include "Utils/Utility.h"

void printUsage()
{
    printf("Usage: fje -f <json file> -s <style> -i <icon family>\n");
    printf("\n");
    printf("Options:\n");
    printf("  -f <json file>    Valid JSON file path\n");
    printf("  -s <style>        Output style, supports tree and rectangle shapes. Default is rectangle\n");
    printf("  -i <icon family>  The name of the icon family needs to be consistent with the ini configuration file, defaulting to pocker face\n");
    printf("\n");
    printf("Example:\n");
    printf("  fje -f test.json -s rect -i pocker-face\n");
    printf("  fje -f test.json -s tree -i realism\n");
}

void parseParam(int argc, char **argv, std::string &filename, std::string &styleName, std::string &iconFamily)
{
    // 选项后面有冒号表示如果指定了该选项，后面必须跟参数
    const char *optStr = "hf:s:i:";
    int opt;
    while ((opt = getopt(argc, argv, optStr)) != -1)
    {
        switch (opt)
        {
        case 'h':
            printUsage();
            exit(0);
        case 'f':
            filename = std::string(optarg);
            break;
        case 's':
            styleName = std::string(optarg);
            break;
        case 'i':
            iconFamily = std::string(optarg);
            break;
        default:
            break;
        }
    }
}

std::unordered_map<std::string, std::pair<std::string, std::string>> readIconFamily(const std::string &iniFilename)
{
    std::unordered_map<std::string, std::pair<std::string, std::string>> iconFamilies;

    // 用文件流读取文件
    std::ifstream ifs(iniFilename);
    if (!ifs.is_open())
    {
        std::cout << "Failed to open ini file: " << iniFilename << "!\n";
        return iconFamilies;
    }

    /**
     * 读取ini文件，文件格式非常简单：
     * 1.配置项用中括号括起来: [section1] ... [section2]
     * 2.具体配置用键值的方式给出: key1=value1
     * 3.注释用分号开头: ; this is comment
     */
    std::string line;
    std::string currentSection;
    while (std::getline(ifs, line))
    {
        // 取出前导空格和末尾空格
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](int ch)
                                              { return !std::isspace(ch); }));
        line.erase(std::find_if(line.rbegin(), line.rend(), [](int ch)
                                { return !std::isspace(ch); })
                       .base(),
                   line.end());
        // 忽略空行和注释行
        if (line.empty() || line[0] == ';')
            continue;

        // 解析section名称
        if (line[0] == '[' && line.back() == ']')
        {
            currentSection = line.substr(1, line.size() - 2);
            continue;
        }

        // 解析键值对
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos)
        {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            if (key == "container")
                iconFamilies[currentSection].first = value;
            else if (key == "leaf")
                iconFamilies[currentSection].second = value;
        }
    }
    // 关闭文件流
    ifs.close();

    return iconFamilies;
}