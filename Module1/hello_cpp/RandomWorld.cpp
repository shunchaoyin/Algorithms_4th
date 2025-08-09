#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // for getpid()

int main()
{
    // 使用时间和进程ID作为种子，提高随机性
    std::srand(std::time(nullptr) + getpid()); // 简单但有效的种子

    std::string champion; // 默认构造为空字符串
    int i = 0;
    std::string word;

    // 实现Knuth的水库采样算法
    while (std::cin >> word)
    {
        ++i;
        // 以概率 1/i 选择当前单词作为冠军
        if (std::rand() % i == 0)
        {
            champion = word;
        }
    }

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