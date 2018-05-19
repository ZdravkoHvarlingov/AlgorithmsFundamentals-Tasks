// There are N cities, M fine paths betweem them and K paths which need to be reconstructed.
// Find the minimum overall cost of reconstruction such that all cities become connected.

#include <iostream>
#include <queue>
#include <math.h>
#include <iomanip>
#include <map>
#include <string>

int parent[10000];
int rank[10000];

int Find(int node)
{
        if (parent[node] == -1)
        {
                return node;
        }

        parent[node] = Find(parent[node]);
        return parent[node];
}

void Union(int first, int second)
{
        int fParent = Find(first);
        int sParent = Find(second);

        int minRank = rank[fParent] < rank[sParent] ? fParent : sParent;
        int maxRank = rank[fParent] < rank[sParent] ? sParent : fParent;

        parent[minRank] = maxRank;
        if (rank[minRank] == rank[maxRank])
        {
                rank[maxRank] += 1;
        }
}

unsigned int n, m, k;

struct Edge
{
        unsigned int src;
        unsigned int dst;
        unsigned int weight;

        bool operator<(const Edge &other) const
        {
                return weight > other.weight;
        }
};

int main()
{
        std::cin >> n >> m >> k;
        for (size_t i = 0; i < n; i++)
        {
                parent[i] = -1;
                rank[i] = 0;
        }

        std::map<std::string, unsigned int> toId;
        std::priority_queue<Edge> q;

        std::string src, dest;
        unsigned int count = 0;
        for (size_t i = 0; i < m; i++)
        {
                std::cin >> src >> dest;
                if (toId.count(src) == 0)
                {
                        toId[src] = count++;
                }
                if (toId.count(dest) == 0)
                {
                        toId[dest] = count++;
                }

                q.push({ toId[src], toId[dest], 0 });
        }

        unsigned int weight;
        for (size_t i = 0; i < k; i++)
        {
                std::cin >> src >> dest >> weight;
                if (toId.count(src) == 0)
                {
                        toId[src] = count++;
                }
                if (toId.count(dest) == 0)
                {
                        toId[dest] = count++;
                }

                q.push({ toId[src], toId[dest], weight });
        }

        unsigned int result = 0;
        count = 0;

        while (count < n - 1 && !q.empty())
        {
                Edge crr = q.top(); q.pop();

                if (Find(crr.src) != Find(crr.dst))
                {
                        Union(crr.src, crr.dst);
                        ++count;
                        result += crr.weight;
                }
        }

        std::cout << result << "\n";

        return 0;
}