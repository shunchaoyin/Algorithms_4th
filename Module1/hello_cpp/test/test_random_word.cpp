#include <gtest/gtest.h>
#include "../RandomWordSelector.h"
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <chrono>

class RandomWordSelectorTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // 使用固定种子确保测试可重现
        gen.seed(12345);
    }

    std::mt19937 gen;
};

// 测试空输入
TEST_F(RandomWordSelectorTest, EmptyInput)
{
    std::istringstream input("");
    std::string result = RandomWordSelector::selectRandomWord(input, gen);
    EXPECT_TRUE(result.empty());
}

// 测试单个单词
TEST_F(RandomWordSelectorTest, SingleWord)
{
    std::istringstream input("hello");
    std::string result = RandomWordSelector::selectRandomWord(input, gen);
    EXPECT_EQ(result, "hello");
}

// 测试多个单词 - 验证结果是输入中的一个
TEST_F(RandomWordSelectorTest, MultipleWords)
{
    std::istringstream input("apple banana cherry date elderberry");
    std::unordered_set<std::string> expected_words = {
        "apple", "banana", "cherry", "date", "elderberry"};

    std::string result = RandomWordSelector::selectRandomWord(input, gen);
    EXPECT_TRUE(expected_words.find(result) != expected_words.end());
}

// 测试分布均匀性 - 统计测试
TEST_F(RandomWordSelectorTest, UniformDistribution)
{
    const std::vector<std::string> words = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    const int num_trials = 10000;
    std::unordered_map<std::string, int> counts;

    // 重置随机数生成器种子
    std::random_device rd;
    std::mt19937 test_gen(rd());

    // 进行多次测试
    for (int i = 0; i < num_trials; ++i)
    {
        std::string result = RandomWordSelector::selectRandomWord(words, test_gen);
        counts[result]++;
    }

    // 检查每个单词被选中的次数是否在合理范围内
    // 期望值是 num_trials / words.size()
    double expected = static_cast<double>(num_trials) / words.size();
    double tolerance = expected * 0.1; // 10%的误差范围

    for (const auto &word : words)
    {
        EXPECT_GE(counts[word], expected - tolerance)
            << "Word '" << word << "' selected too few times";
        EXPECT_LE(counts[word], expected + tolerance)
            << "Word '" << word << "' selected too many times";
        // 输出每个单词的计数
        std::cout << "Word: " << word << ", Count: " << counts[word] << std::endl;
    }
}

// 测试确定性 - 使用相同种子应产生相同结果
TEST_F(RandomWordSelectorTest, Deterministic)
{
    std::vector<std::string> words = {"one", "two", "three", "four", "five"};

    // 第一次运行
    std::mt19937 gen1(42);
    std::string result1 = RandomWordSelector::selectRandomWord(words, gen1);

    // 第二次运行，使用相同种子
    std::mt19937 gen2(42);
    std::string result2 = RandomWordSelector::selectRandomWord(words, gen2);

    EXPECT_EQ(result1, result2);
}

// 测试大数据集
TEST_F(RandomWordSelectorTest, LargeDataset)
{
    std::ostringstream oss;
    for (int i = 0; i < 1000; ++i)
    {
        oss << "word" << i << " ";
    }

    std::istringstream input(oss.str());
    std::string result = RandomWordSelector::selectRandomWord(input, gen);

    // 结果应该是 word 开头的格式
    EXPECT_TRUE(result.substr(0, 4) == "word");

    // 提取数字部分并验证范围
    std::string number_part = result.substr(4);
    int word_index = std::stoi(number_part);
    EXPECT_GE(word_index, 0);
    EXPECT_LT(word_index, 1000);
}

// 测试边界情况 - 两个单词
TEST_F(RandomWordSelectorTest, TwoWords)
{
    const std::vector<std::string> words = {"first", "second"};
    const int num_trials = 1000;
    int first_count = 0;

    std::random_device rd;
    std::mt19937 test_gen(rd());

    for (int i = 0; i < num_trials; ++i)
    {
        std::string result = RandomWordSelector::selectRandomWord(words, test_gen);
        if (result == "first")
        {
            first_count++;
        }
    }

    // 理论上"first"被选中的概率应该接近50%
    double ratio = static_cast<double>(first_count) / num_trials;
    EXPECT_GE(ratio, 0.4); // 至少40%
    EXPECT_LE(ratio, 0.6); // 最多60%
}

// 性能测试 - 验证算法能处理大输入
TEST_F(RandomWordSelectorTest, PerformanceTest)
{
    std::ostringstream oss;
    const int large_size = 100000;

    for (int i = 0; i < large_size; ++i)
    {
        oss << "item" << i << " ";
    }

    std::istringstream input(oss.str());

    // 测量执行时间
    auto start = std::chrono::high_resolution_clock::now();
    std::string result = RandomWordSelector::selectRandomWord(input, gen);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // 验证结果正确
    EXPECT_FALSE(result.empty());
    EXPECT_TRUE(result.substr(0, 4) == "item");

    // 性能检查 - 应该在合理时间内完成（这个阈值可以根据需要调整）
    EXPECT_LT(duration.count(), 1000) << "Algorithm took too long: " << duration.count() << "ms";
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
