#include <iostream>
#include <string>
#include "RandomWordSelector.h"

int main()
{
    // 使用重构后的类进行水库采样
    std::string champion = RandomWordSelector::selectRandomWord(std::cin);

    // 输出结果
    if (!champion.empty())
    {
        std::cout << champion << std::endl;
    }
    else
    {
        std::cerr << "No words were read." << std::endl;
    }

    return 0;
}