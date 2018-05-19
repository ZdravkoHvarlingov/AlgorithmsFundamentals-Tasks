// Task: Find the longest route from source vertex 0 in a DAG
// More direct approach can be used - topological sorting + longest path in DAG algorithm

#include <iostream>
#include <vector>

struct Edge
{
        short dest;
        short weight;
};

struct Node
{
        bool foundMax;
        unsigned int max;
        std::vector<Edge> edges;
};

std::vector<Node> graph;
unsigned int n;
unsigned int m;

unsigned int GetMax(unsigned short crrNode)
{
        unsigned int max = 0;

        for (size_t i = 0; i < graph[crrNode].edges.size(); i++)
        {
                short next = graph[crrNode].edges[i].dest;
                short distance = graph[crrNode].edges[i].weight;

                if (!graph[next].foundMax)
                {
                        graph[next].max = GetMax(next);
                        graph[next].foundMax = true;
                }
                unsigned int crr = graph[next].max + distance;

                if (crr > max)
                {
                        max = crr;
                }
        }

        return max;
}

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin >> n;
        std::cin >> m;
        graph.assign(n, { false, 0 });

        short left, right, weight;
        for (size_t i = 0; i < m; i++)
        {
                std::cin >> left;
                std::cin >> right;
                --left;
                --right;

                std::cin >> weight;
                graph[left].edges.push_back({ right, weight });
        }

        std::cout << GetMax(0) << "\n";

        return 0;
}