#pragma once
#include <string>
#include <vector>
#include <random>
#include <istream>

class RandomWordSelector
{
public:
    // 使用指定的随机数生成器进行水库采样
    static std::string selectRandomWord(std::istream &input, std::mt19937 &gen);

    // 使用默认随机数生成器
    static std::string selectRandomWord(std::istream &input);

    // 从字符串向量中选择随机单词（用于测试）
    static std::string selectRandomWord(const std::vector<std::string> &words, std::mt19937 &gen);
};
