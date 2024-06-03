#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <unistd.h>

/**
 * @description: 打印程序用法
 * @return {*}
 */
void printUsage();

/**
 * @description: 解析命令行参数，有四个参数需要解析：-hfsi，其中-f必须指定参数，如果指定了-h则不执行程序
 * @param {int} argc
 * @param {char**} argv
 * @return {*}
 */
void parseParam(int argc, char **argv, std::string &filename, std::string &styleName, std::string &iconFamily);

/**
 * @description: 读取ini配置文件中的图标族
 * @param {string} &iniFilename ini配置文件路径
 * @return {*} 键值结构，键为图标族的名称，值为Container和Leaf对应的图标
 */
std::unordered_map<std::string, std::pair<std::string, std::string>> readIconFamily(const std::string &iniFilename);