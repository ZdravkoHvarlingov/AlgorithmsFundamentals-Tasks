// The input graph is a inheritance scheme.
// Find if that inheritance is a diamond one.

#include <iostream>
#include <vector>
#include <bitset>

short t, n, m;
std::vector<std::vector<short>> graph;
std::bitset<1000> hasZeroInput;
std::bitset<1000> visited;

bool Visit(short node)
{
        visited.set(node, true);

        std::vector<short> &edges = graph[node];
        for (size_t i = 0; i < edges.size(); i++)
        {
                if (visited.test(edges[i]) == false)
                {
                        bool result = Visit(edges[i]);
                        if (result)
                        {
                                return true;
                        }
                }
                else
                {
                        return true;
                }
        }

        return false;
}

//start is always 0 considering the input
bool HasTwoPaths()
{
        for (size_t i = 0; i < n; i++)
        {
                if (hasZeroInput.test(i) == true)
                {
                        visited.reset();

                        bool result = Visit(i);
                        if (result == true)
                        {
                                return true;
                        }
                }
        }

        return false;
}

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin >> t;
        for (size_t i = 0; i < t; i++)
        {
                std::cin >> n;

                graph.clear();
                graph.assign(n, std::vector<short>());
                hasZeroInput.reset();
                hasZeroInput.flip();
                for (size_t j = 0; j < n; j++)
                {
                        std::cin >> m;
                        short edge;
                        for (size_t k = 0; k < m; k++)
                        {
                                std::cin >> edge;
                                --edge;
                                graph[j].push_back(edge);
                                hasZeroInput.set(edge, false);
                        }
                }

                bool hasTwoPaths = HasTwoPaths();
                std::cout << "Case #" << i + 1 << ": ";
                if (hasTwoPaths)
                {
                        std::cout << "Yes\n";
                }
                else
                {
                        std::cout << "No\n";
                }
        }

    return 0;
}