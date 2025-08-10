#include "RandomWordSelector.h"
#include <iostream>
#include <sstream>

std::string RandomWordSelector::selectRandomWord(std::istream &input, std::mt19937 &gen)
{
    std::string champion;
    int i = 0;
    std::string word;

    // 实现Knuth的水库采样算法
    while (input >> word)
    {
        ++i;
        // 定义分布范围 [1, i]
        std::uniform_int_distribution<int> dist(1, i);

        // 生成随机数
        int random_num = dist(gen);
        // 以概率 1/i 选择当前单词作为冠军
        if (random_num == 1)
        {
            champion = word;
        }
    }

    return champion;
}

std::string RandomWordSelector::selectRandomWord(std::istream &input)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    return selectRandomWord(input, gen);
}

std::string RandomWordSelector::selectRandomWord(const std::vector<std::string> &words, std::mt19937 &gen)
{
    if (words.empty())
    {
        return "";
    }

    std::string champion = words[0];

    for (size_t i = 1; i < words.size(); ++i)
    {
        std::uniform_int_distribution<int> dist(1, static_cast<int>(i + 1));
        int random_num = dist(gen);

        if (random_num == 1)
        {
            champion = words[i];
        }
    }

    return champion;
}
