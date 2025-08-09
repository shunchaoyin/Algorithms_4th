#include <iostream>
#include <string>
int main(int argc, char* argv[])
{

    if (argc == 3) {
        std::cout << "Hello " << argv[1] << " and " << argv[2] << "." << std::endl;
        std::cout << "Goodbye " << argv[2] << " and " << argv[1] << "." << std::endl;
    } else {
        std::cerr << "Usage: " << argv[0] << " <name1> <name2>" << std::endl;
    }
    return 0;
}