#pragma once

#include <exception>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <algorithm>

/**
 * 自定义的Unicode字符串，如果要添加字符请使用appendCh方法，如果要添加std::string类型请使用+=操作或者appendStr方法
 */
class UString
{
private:
  std::list<std::string> mStr;

public:
  UString() = default;
  ~UString() = default;
  UString(const UString &other);
  UString(UString &&other);
  UString(const std::string &str);

  /**
   * @description: 返回Unicode字符target第一次出现的下标
   * @param {string&} target
   * @return {int} 第一次出现的下标，如果没有出现则返回-1
   */
  int find_first_of(const std::string &target) const;

  /**
   * @description: 添加一个Unicode字符，支持链式调用
   * @param {string&} c
   * @return {UString&}
   */
  UString &appendCh(const std::string &c);

  /**
   * @description: 添加字符串，支持链式调用
   * @param {string} &str
   * @return {UString&}
   */
  UString &appendStr(const std::string &str);

  /**
   * @description: 返回字符串长度
   * @return {int}
   */
  int length() const;

  /**
   * @description: 判断字符串是否为空
   * @return {bool}
   */
  bool empty() const;

  /**
   * @description: 判断某个位置是否是ASCII字母
   * @param {int} idx
   * @return {bool}
   */
  bool isAlpha(int idx) const;

  /**
   * @description: 替换某个位置的字符
   * @param {int} pos
   * @param {string&} str
   * @return {*}
   */
  void replaceCh(int pos, const std::string &str);

  /**
   * @description: 将UString转成std::string并返回
   * @return {*}
   */  
  std::string toString();

  /**
   * @description:
   * 重载[]运算符，用户可以像使用数组一样使用UString，只不过效率较低
   * @param {int} idx 索引
   * @return {string&}
   */
  std::string &operator[](int idx);

  /**
   * @description:
   * 重载=号运算符，std::list<std::string>会自动进行深拷贝所以不用进行特殊处理
   * @return {*}
   */
  UString &operator=(const UString &other);

  /**
   * @description: 重载==运算符，用于判断两个UString是否相等
   * @param {UString&} other
   * @return {bool}
   */
  bool operator==(const UString &other);

  /**
   * @description:
   * 重载+=运算符，将当前对象和UString相加后返回，这里保持和直觉一样不支持链式调用，一般也没有a+=b+=c这种用法
   * @return {void}
   */
  void operator+=(const UString &other);

  /**
   * @description:
   * 重载+=运算符以支持对std::string的加操作，注意这里将std::string当成字符串而不是字符
   * @return {*}
   */
  void operator+=(const std::string &str);

  /**
   * @description: 重载<<即输出运算符，支持std::cout打印字符串
   * @return {*}
   */
  friend std::ostream &operator<<(std::ostream &out, const UString &str);
};


