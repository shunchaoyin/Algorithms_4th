#include "../RandomWordSelector.h"
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <chrono>
#include <cassert>
#include <vector>

// 简单的测试框架
class TestRunner
{
private:
    int passed = 0;
    int failed = 0;
    std::string current_test;

public:
    void start_test(const std::string &name)
    {
        current_test = name;
        std::cout << "Running: " << name << "... ";
    }

    void assert_true(bool condition, const std::string &message = "")
    {
        if (condition)
        {
            std::cout << "PASS" << std::endl;
            passed++;
        }
        else
        {
            std::cout << "FAIL";
            if (!message.empty())
            {
                std::cout << " - " << message;
            }
            std::cout << std::endl;
            failed++;
        }
    }

    void assert_equal(const std::string &expected, const std::string &actual)
    {
        bool result = (expected == actual);
        if (result)
        {
            std::cout << "PASS" << std::endl;
            passed++;
        }
        else
        {
            std::cout << "FAIL - Expected '" << expected << "', got '" << actual << "'" << std::endl;
            failed++;
        }
    }

    void print_summary()
    {
        std::cout << "\n=== Test Summary ===" << std::endl;
        std::cout << "Passed: " << passed << std::endl;
        std::cout << "Failed: " << failed << std::endl;
        std::cout << "Total: " << (passed + failed) << std::endl;
        if (failed == 0)
        {
            std::cout << "All tests passed! ✅" << std::endl;
        }
    }

    bool all_passed() const { return failed == 0; }
};

void test_empty_input(TestRunner &runner)
{
    runner.start_test("Empty Input");
    std::istringstream input("");
    std::mt19937 gen(12345);
    std::string result = RandomWordSelector::selectRandomWord(input, gen);
    runner.assert_true(result.empty());
}

void test_single_word(TestRunner &runner)
{
    runner.start_test("Single Word");
    std::istringstream input("hello");
    std::mt19937 gen(12345);
    std::string result = RandomWordSelector::selectRandomWord(input, gen);
    runner.assert_equal("hello", result);
}

void test_multiple_words(TestRunner &runner)
{
    runner.start_test("Multiple Words");
    std::istringstream input("apple banana cherry");
    std::mt19937 gen(12345);
    std::unordered_set<std::string> expected_words = {"apple", "banana", "cherry"};

    std::string result = RandomWordSelector::selectRandomWord(input, gen);
    bool valid = expected_words.find(result) != expected_words.end();
    runner.assert_true(valid, "Result should be one of the input words, got: " + result);
}

void test_deterministic_behavior(TestRunner &runner)
{
    runner.start_test("Deterministic Behavior");
    std::vector<std::string> words = {"one", "two", "three", "four"};

    std::mt19937 gen1(42);
    std::string result1 = RandomWordSelector::selectRandomWord(words, gen1);

    std::mt19937 gen2(42);
    std::string result2 = RandomWordSelector::selectRandomWord(words, gen2);

    runner.assert_equal(result1, result2);
}

void test_uniform_distribution(TestRunner &runner)
{
    runner.start_test("Uniform Distribution");
    const std::vector<std::string> words = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    const int num_trials = 3000;
    std::unordered_map<std::string, int> counts;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < num_trials; ++i)
    {
        std::string result = RandomWordSelector::selectRandomWord(words, gen);
        counts[result]++;
    }

    // 检查分布是否合理（每个词应该大约被选中 num_trials/3 次）
    double expected = static_cast<double>(num_trials) / words.size();
    bool distribution_ok = true;

    for (const auto &word : words)
    {
        std::cout << "Word: " << word << ", Count: " << counts[word] << std::endl;
        double ratio = static_cast<double>(counts[word]) / expected;
        // 允许30%的偏差
        if (ratio < 0.7 || ratio > 1.3)
        {
            distribution_ok = false;
            break;
        }
    }

    runner.assert_true(distribution_ok, "Distribution should be roughly uniform");
}

void test_large_dataset(TestRunner &runner)
{
    runner.start_test("Large Dataset");
    std::ostringstream oss;
    for (int i = 0; i < 1000; ++i)
    {
        oss << "word" << i << " ";
    }

    std::istringstream input(oss.str());
    std::mt19937 gen(12345);
    std::string result = RandomWordSelector::selectRandomWord(input, gen);

    bool valid = result.substr(0, 4) == "word" && !result.empty();
    runner.assert_true(valid, "Result should be in correct format");
}

void test_performance(TestRunner &runner)
{
    runner.start_test("Performance Test");
    std::ostringstream oss;
    const int large_size = 50000;

    for (int i = 0; i < large_size; ++i)
    {
        oss << "item" << i << " ";
    }

    std::istringstream input(oss.str());
    std::mt19937 gen(12345);

    auto start = std::chrono::high_resolution_clock::now();
    std::string result = RandomWordSelector::selectRandomWord(input, gen);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    bool performance_ok = !result.empty() && duration.count() < 500; // 500ms threshold
    runner.assert_true(performance_ok, "Should complete in reasonable time");
}

int main()
{
    TestRunner runner;

    std::cout << "=== Random Word Selector Tests ===" << std::endl;

    test_empty_input(runner);
    test_single_word(runner);
    test_multiple_words(runner);
    test_deterministic_behavior(runner);
    test_uniform_distribution(runner);
    test_large_dataset(runner);
    test_performance(runner);

    runner.print_summary();

    return runner.all_passed() ? 0 : 1;
}
