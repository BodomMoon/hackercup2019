// Round2Q2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

static vector<int> pays{1};
static const auto MOD = 1000000007;

void updatePay(int n) {
    if (n <= pays.size() - 1) {
        return;
    }
    while (n >= pays.size()) {
        pays.push_back((pays.back() * 2) % MOD);
    }
    return;
}

int solution() {
    int useless, maxCnt;

    cin >> useless;
    cin >> maxCnt;

    string input;
    cin >> input;
    
    updatePay(input.size());

    auto result = 0;

    auto cnt = 0;
    for (int i = input.size() - 1; i >= 0; --i) {
        switch (input[i]) {
        case 'B':
            cnt++;
            if (cnt > maxCnt) {
                result = (result + pays[i + 1]) % MOD;
                cnt = max(0, cnt - 2);
            }
            break;
        case 'A':
            cnt = max(0, cnt - 1);
            break;
        }
    }
    return result;
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