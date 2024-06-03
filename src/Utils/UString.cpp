#include "Utils/UString.h"

UString::UString(const UString &other) : mStr(other.mStr) {}
UString::UString(UString &&other) : mStr(std::move(other.mStr)) {}
UString::UString(const std::string &str)
{
    for (const char &ch : str)
        mStr.push_back(std::to_string(ch));
}

int UString::find_first_of(const std::string &target) const
{
    int ans = -1;
    for (auto it = mStr.begin(); it != mStr.end(); it++)
    {
        if (*it == target)
        {
            ans = std::distance(mStr.begin(), it);
            break;
        }
    }
    return ans;
}

UString &UString::appendCh(const std::string &c)
{
    if (!c.empty())
        mStr.push_back(c);
    return *this;
}

UString &UString::appendStr(const std::string &str)
{
    for (const char &ch : str)
        mStr.push_back(std::string(1, ch));
    return *this;
}

int UString::length() const { return mStr.size(); }

bool UString::empty() const { return mStr.empty(); }

bool UString::isAlpha(int idx) const
{
    if (idx < 0 || idx >= mStr.size())
        return false;
    auto it = mStr.begin();
    while (idx--)
        it++;
    if (it->length() == 1 && ((it->at(0) >= 97 && it->at(0) <= 122) ||
                              (it->at(0) >= 65 && it->at(0) <= 90)))
        return true;
    return false;
}

void UString::replaceCh(int pos, const std::string &str)
{
    if (pos < 0 || pos >= mStr.size())
        return;
    auto it = mStr.begin();
    while (pos--)
        it++;
    *it = str;
}

std::string UString::toString()
{
    std::string ret = "";
    for (auto it = mStr.begin(); it != mStr.end(); it++)
        ret += *it;
    return ret;
}

std::string &UString::operator[](int idx)
{
    if (idx < 0 || idx > mStr.size())
        throw std::out_of_range("Invalid index!");
    auto it = mStr.begin();
    while (idx--)
        it++;
    return *it;
}

UString &UString::operator=(const UString &other)
{
    if (this != &other)
        mStr = other.mStr;
    return *this;
}

bool UString::operator==(const UString &other)
{
    if (this == &other)
        return true;

    auto mIt = mStr.begin();
    auto oIt = other.mStr.begin();
    while (mIt != mStr.end() && oIt != other.mStr.end())
    {
        if (*mIt != *oIt)
            return false;
        mIt++, oIt++;
    }
    return mIt == mStr.end() && oIt == other.mStr.end();
}

void UString::operator+=(const UString &other)
{
    auto it = other.mStr.begin();
    while (it != other.mStr.end())
        mStr.push_back(*it++);
}

void UString::operator+=(const std::string &str)
{
    for (const char &ch : str)
        mStr.push_back(std::string(1, ch));
}

std::ostream &operator<<(std::ostream &out, const UString &str)
{
    for (auto it = str.mStr.begin(); it != str.mStr.end(); it++)
        out << *it;
    return out;
}