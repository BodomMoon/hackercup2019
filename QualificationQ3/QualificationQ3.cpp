#include <iostream>
#include <string>
#include <algorithm>

static const uint64_t MOD = 1000000007;

uint64_t getPower(int unsigned y)
{
    uint64_t res = 1;     // Initialize result 
    uint64_t x = 2;
    auto p = MOD;

    while (y > 0)
    {
        // If y is odd, multiply x with result 
        if (y & 1)
            res = (res*x) % p;

        // y must be even now 
        y = y >> 1; // y = y/2 
        x = (x*x) % p;
    }

    return res;
}

int solution() {
    using namespace std;
    int size, K;
    cin >> size;
    cin >> K;
    string input;
    cin >> input;
    uint64_t pay = 0;

    int cnt = 0;
    for (auto i = size - 1; i >= 0; --i) {
        switch (input[i]) {
        case 'A':
            cnt = max(0, cnt - 1);
            break;
        case 'B':
            if (cnt == K) {
                uint64_t price = 1;
                pay = (pay + getPower(i + 1)) % MOD;
                cnt--;
            }
            else {
                cnt++;
            }
            break;
        }
    }
    return pay;
}

int main()
{
    int testCase = 0;
    std::cin >> testCase;

    for (auto i = 0; i < testCase; ++i) {
        const auto result = solution();
        std::cout << "Case #" << i + 1 << ": " << result << std::endl;
    }

    return 0;
}