#include "JsonParser/Component.h"

Component::Component() : mKey("") {}
Component::Component(const std::string &key) : mKey(key) {}
Component::~Component() {}

Leaf::Leaf() {}
Leaf::Leaf(const std::string &key) : Component(key) {}
Leaf::Leaf(const std::string &key, const std::string &value) : Component(key), mVal(value) {}
Leaf::~Leaf() {}

std::string Leaf::getStrValue()
{
    return this->mVal;
}

void Leaf::setValue(const std::string &value)
{
    this->mVal = value;
}

std::string Leaf::getKey()
{
    return mKey;
}

void Leaf::setKey(const std::string &key)
{
    this->mKey = key;
}

std::string Leaf::draw()
{
    if (mVal.empty())
        return mKey;
    return mKey + ": " + mVal;
}

Container::Container() {}
Container::Container(const std::string &key) : Component(key) {}
Container::~Container() {}

void Container::setName(const std::string &key)
{
    this->mKey = key;
}

void Container::addComponent(std::shared_ptr<Component> component)
{
    mInnerComponents.push_back(component);
}

std::vector<std::shared_ptr<Component>> &Container::getComponents()
{
    return mInnerComponents;
}

std::string Container::draw()
{
    return mKey;
}