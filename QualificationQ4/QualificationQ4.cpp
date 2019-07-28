#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <stack>

namespace {
    typedef std::vector<std::vector<int>> conditions;
    typedef std::unordered_map<int, std::set<int>> dicts;
    typedef std::vector<std::set<int>> trees;

    bool MakeRoot(const int root, const conditions& LCAs,const std::set<int>& nodes, dicts& isNeighbors, dicts& notNeighbors) {
        for (const auto& LCA : LCAs) {
            int x = LCA[0], y = LCA[1], z = LCA[2];
            if (nodes.find(x) == nodes.end() || nodes.find(y) == nodes.end() || nodes.find(z) == nodes.end()) {
                continue;
            }
            if (x == root || y == root) {
                if (z != root) {
                    return false;
                }
            }
            else if (z == root) {
                notNeighbors[x].insert(y);
                notNeighbors[y].insert(x);
            }
            else {
                isNeighbors[x].insert(y);
                isNeighbors[x].insert(z);
                isNeighbors[y].insert(x);
                isNeighbors[y].insert(z);
                isNeighbors[z].insert(x);
                isNeighbors[z].insert(y);
            }
        }
        return true;
    }

    bool MakeSubtree(const int root, const std::set<int>& nodes, dicts& isNeighbors, dicts& notNeighbors, trees& subtrees) {
        using namespace std;
        unordered_map<int, int> passed;
        passed[root] = 1;
        for (const auto& node : nodes) {
            if (passed.find(node) != passed.end()) {
                continue;
            }
            passed[node] = 1;
            set<int> subtree;
            stack<int> builder;
            builder.push(node);
            while (!builder.empty()) {
                const auto cur = builder.top();
                builder.pop();
                subtree.insert(cur);
                for (const auto& neighbor: isNeighbors[cur]) {
                    if (passed.find(neighbor) != passed.end()) {
                        continue;
                    }
                    passed[neighbor] = 1;
                    builder.push(neighbor);
                }
            }
            auto curIter = subtree.begin();
            for (auto i = 0; i < subtree.size(); ++i, curIter++) {
                auto nextIter = subtree.begin();
                for (auto j = 0; j < i; ++j, nextIter++) {
                    if (notNeighbors[*curIter].find(*nextIter) != notNeighbors[*curIter].end()) {
                        return false;
                    }
                }
            }
            subtrees.push_back(subtree);
        }
        return true;
    }

    bool Helper(int root, const conditions& LCAs,const std::set<int> nodes, std::vector<int>& result) {
        for (const auto& node : nodes) {
            dicts isNeighbor;
            dicts notNeighbor;
            if (MakeRoot(node, LCAs, nodes, isNeighbor, notNeighbor) == false) {
                continue;
            }
            trees subtrees;
            if (MakeSubtree(node, nodes, isNeighbor, notNeighbor, subtrees) == false) {
                continue;
            }
            result[node] = root;
            for (const auto& subtree : subtrees) {
                if (Helper(node, LCAs, subtree, result) == false)
                    return false;
            }
            return true;
        }
        return false;
    }

    std::vector<int> Solution() {
        using namespace std;

        conditions LCAs{};
        int nodeCount, limitCount;
        cin >> nodeCount;
        cin >> limitCount;

        for (auto i = 0; i < limitCount; ++i) {
            vector<int> LCA{};
            auto x = 0, y = 0, z = 0;
            cin >> x >> y >> z;
            LCA.push_back(x - 1);
            LCA.push_back(y - 1);
            LCA.push_back(z - 1);
            LCAs.push_back(LCA);
        }
        vector<int> result(nodeCount, 0);
        set<int> nodes;
        for (int i = 0; i < nodeCount; ++i) {
            nodes.insert(nodes.end(), i);
        }
        if (Helper(-1, LCAs, nodes, result) == false) {
            return {};
        }
        return result;
    }
}

int main()
{
    int testCase = 0;
    std::cin >> testCase;

    for (auto i = 0; i < testCase; ++i) {
        const auto result = Solution();
        if (result.empty())
            std::cout << "Case #" << i + 1 << ": " << "Impossible" << std::endl;
        else {
            std::cout << "Case #" << i + 1 << ": ";
            for (const auto& v : result) {
                std::cout << v + 1 << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}