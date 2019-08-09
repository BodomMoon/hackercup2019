// Round2Q1.cpp

#include <iostream>
#include <vector>

bool solution() {
    using namespace std;
    int useless;
    int people;
    cin >> useless;
    cin >> useless;
    cin >> people;
    vector<int> X(2, 0);
    cin >> X[0];
    cin >> X[1];
    vector<vector<int>> tracers(people, vector<int>(2,0));
    for (auto i = 0; i < people; ++i) {
        cin >> tracers[i][0];
        cin >> tracers[i][1];
    }
    if (people == 1) {
        return false;
    }

    for (const auto& tracer : tracers) {
        if ((abs(X[0] - tracer[0]) + abs(X[1] - tracer[1])) % 2 != 0)
            return false;
    }
    return true;
}

int main()
{
    int testCase = 0;
    std::cin >> testCase;

    for (auto i = 0; i < testCase; ++i) {
        const auto result = solution();
        std::cout << "Case #" << i + 1 << ": " << (result ? "Y" : "N") << std::endl;
    }
    return 0;
}
