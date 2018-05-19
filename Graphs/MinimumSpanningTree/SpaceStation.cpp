// There is a space station with N zones and damaged corridors between them.
// M is the amount of all damaged corridors, and K is the amount of NON damaged ones.
// The corridors (edges), which are damaged, have weights, which indicates the time needed for repairment.
// Task: Find the minimum time in order to connect all the N zones.

#include <iostream>
#include <queue>

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

        std::priority_queue<Edge> q;
        unsigned int src, dst, weight;
        for (size_t i = 0; i < m; i++)
        {
                std::cin >> src >> dst >> weight;
                --src;
                --dst;

                q.push({ src, dst, weight });
        }

        for (size_t i = 0; i < k; i++)
        {
                std::cin >> src >> dst;
                
                --src;
                --dst;
                q.push({ src, dst, 0 });
        }

        unsigned long long result = 0;
        unsigned int count = 0;

        while (!q.empty())
        {
                Edge crr = q.top(); q.pop();

                if (count < n - 1 && Find(crr.src) != Find(crr.dst))
                {
                        Union(crr.src, crr.dst);
                        ++count;

                        result += crr.weight;
                }
        }

        if (count < n - 1)
        {
                std::cout << -1 << "\n";
        }
        else std::cout << result << "\n";

        return 0;
}