#include "JsonParser/JsonParser.h"

char Tokenizer::mGetCharacter()
{
    if (!mFile.good())
        return ' ';
    char c = ' ';
    while ((c == ' ') || c == '\n')
    {
        mFile.get(c);
        if (!mFile.good())
            return c;
    }
    return c;
}
Tokenizer::Tokenizer(const std::string &fileName)
{
    mFile.open(fileName);
    if (!mFile.is_open())
        std::cout << "Failed to open file " << fileName << std::endl;
}

bool Tokenizer::hasNextToken()
{
    return !mFile.eof();
}

Token Tokenizer::getToken()
{
    char c;
    if (mFile.eof())
        throw "End of file!!";
    mPrevPos = mFile.tellg();
    c = mGetCharacter();
    Token token;
    if (c == '"')
    {
        token.type = TOKEN_TYPE::STRING;
        token.val = "";
        mFile.get(c);
        while (c != '"')
        {
            token.val += c;
            mFile.get(c);
        }
    }
    else if (c == '{')
    {
        token.type = TOKEN_TYPE::OPEN_BRACE;
    }
    else if (c == '}')
    {
        token.type = TOKEN_TYPE::CLOSE_BRACE;
    }
    else if (c == '-' || (c >= '0' && c <= '9'))
    {
        token.type = TOKEN_TYPE::NUMBER;
        token.val = "";
        token.val += c;
        std::streampos prevCharPos = mFile.tellg();
        while ((c == '-') || (c >= '0' && c <= '9') || c == '.')
        {
            prevCharPos = mFile.tellg();
            mFile.get(c);

            if (mFile.eof())
                break;
            else
            {
                if ((c == '-') || (c >= '0' && c <= '9') || (c == '.'))
                    token.val += c;
                else
                    mFile.seekg(prevCharPos);
            }
        }
    }
    // 值为null
    else if (c == 'n')
    {
        token.type = TOKEN_TYPE::NULL_TYPE;
        mFile.seekg(3, std::ios_base::cur);
    }
    else if (c == ':')
        token.type = TOKEN_TYPE::COLON;
    else if (c == ',')
        token.type = TOKEN_TYPE::COMMA;

    return token;
}

void Tokenizer::reOpen(const std::string &fileName)
{
    if (mFile.is_open())
        mFile.close();
    mFile.open(fileName);
    if (!mFile.is_open())
        std::cout << "Failed to open file " << fileName << std::endl;
}

JsonParser::JsonParser(const std::string &filename) : mTokenizer(filename), mRoot(nullptr) {}

std::shared_ptr<JsonParser> JsonParser::getInstance(const std::string &filename)
{
    // 如果为空则创建一个
    if (jsonParser == nullptr)
    {
        jsonParser = std::shared_ptr<JsonParser>(new JsonParser(filename));
        return jsonParser;
    }
    // 否则重新打开文件
    jsonParser->reOpen(filename);
    return jsonParser;
}

void JsonParser::parse()
{
    // 保存解析过程中的key，因为在解析到key的时候还不知道对应的是Leaf还是Container
    std::string key = "";

    while (mTokenizer.hasNextToken())
    {
        Token token;
        try
        {
            token = mTokenizer.getToken();
            switch (token.type)
            {
            /**
             * 解析到字符串，判断它是key还是value：
             * 1.如果是key则保存
             * 2.如果是value则创建Leaf并将key清空
             */
            case TOKEN_TYPE::STRING:
            {
                if (key.empty())
                {
                    key = token.val;
                }
                else
                {
                    std::shared_ptr<Leaf> newLeaf = std::make_shared<Leaf>(key, token.val);
                    key.clear();
                    mParseStack.top()->addComponent(newLeaf);
                }
            }
            break;
            // 解析到数字则创建Leaf并添加到Container中
            case TOKEN_TYPE::NUMBER:
            {
                if (key.empty())
                    throw std::logic_error("Invalid Json Format!!");
                std::shared_ptr<Leaf> newLeaf = std::make_shared<Leaf>(key, token.val);
                key.clear();
                mParseStack.top()->addComponent(newLeaf);
            }
            break;
            // 遇到冒号则判断合法性，如果key为空则不合法
            case TOKEN_TYPE::COLON:
            {
                if (key.empty())
                    throw std::logic_error("Invalid Json Format!!");
            }
            break;
            // 遇到逗号则判断合法性：如果key不为空则不合法
            case TOKEN_TYPE::COMMA:
            {
                if (!key.empty())
                    throw std::logic_error("Invalid Json Format!!");
            }
            break;
            // 遇到开大括号 { 则创建Container并压栈
            case TOKEN_TYPE::OPEN_BRACE:
            {
                std::shared_ptr<Container> newContainer;
                // 是否是根结点，如果是根节点则Container没有key
                if (key.empty())
                {
                    if (mRoot != nullptr)
                        throw std::logic_error("Invalid Json Format!!");

                    newContainer = std::make_shared<Container>();
                    mRoot = newContainer;
                }
                else
                {
                    newContainer = std::make_shared<Container>(key);
                    key.clear();
                    mParseStack.top()->addComponent(newContainer);
                }
                mParseStack.push(newContainer);
            }
            break;
            // 遇到闭大括号 } 则弹栈
            case TOKEN_TYPE::CLOSE_BRACE:
            {
                if (mParseStack.empty())
                    throw std::logic_error("Invalid Json Format!!");
                mParseStack.pop();
            }
            break;
            // 遇到null则创建Leaf，这个Leaf的value是空
            case TOKEN_TYPE::NULL_TYPE:
            {
                if (key.empty())
                    throw std::logic_error("Invalid Json Format!!");
                std::shared_ptr<Leaf> newLeaf = std::make_shared<Leaf>(key);
                mParseStack.top()->addComponent(newLeaf);
                key.clear();
            }
            break;
            default:
                break;
            }
        }
        catch (std::logic_error e)
        {
            break;
        }
    }
}

std::shared_ptr<Container> JsonParser::getRoot()
{
    return mRoot;
}
void JsonParser::reOpen(const std::string &filename)
{
    mTokenizer.reOpen(filename);
}

// 类内的静态变量必须在类外进行初始化
std::shared_ptr<JsonParser> JsonParser::jsonParser = nullptr;