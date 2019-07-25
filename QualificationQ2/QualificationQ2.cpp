#include <iostream>
#include <string>

int main()
{
    int testCase = 0;
    std::cin >> testCase;

    for (auto i = 0; i < testCase; ++i) {
        std::string input;
        std::cin >> input;
        int Bcount = 0;

        for (const auto& v : input) {
            if (v == 'B') {
                Bcount++;
            }
        }

        auto result = 'Y';
        if (input.size() <= 2 || Bcount < 2 || Bcount == input.size() - 1) {
            result = 'N';
        }

        std::cout << "Case #" << std::to_string(i + 1) << ": " << result << std::endl;
    }
}