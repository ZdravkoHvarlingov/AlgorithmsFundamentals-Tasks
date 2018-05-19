// There are N points with x and y coordinates.
// Task: find the minimum overall distance such that all points are connected. 
// (Minimum spanning tree with N nodes and edges - distance between the nodes)

#include <iostream>
#include <queue>
#include <math.h>
#include <iomanip>

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

unsigned int n;

struct Point
{
        unsigned short id;
        double x, y;
};

struct Edge
{
        Point src;
        Point dst;

        double weight;

        void CalcWeight()
        {
                weight = std::sqrt(std::abs(src.x - dst.x) * std::abs(src.x - dst.x) + std::abs(src.y - dst.y) * std::abs(src.y - dst.y));
        }

        bool operator<(const Edge &other) const
        {
                return weight > other.weight;
        }
};

Point points[1000];

int main()
{
        std::cin >> n;
        for (size_t i = 0; i < n; i++)
        {
                parent[i] = -1;
                rank[i] = 0;
        }
        for (size_t i = 0; i < n; i++)
        {
                double x, y;
                std::cin >> x >> y;

                points[i] = { (unsigned short)i, x, y };
        }

        std::priority_queue<Edge> q;

        for (size_t i = 0; i < n; i++)
        {
                for (size_t j = i + 1; j < n; j++)
                {
                        Edge newEdge = { points[i], points[j], 0 };
                        newEdge.CalcWeight();

                        q.push(newEdge);
                }
        }

        double result = 0;
        unsigned int count = 0;

        while (count < n - 1 && !q.empty())
        {
                Edge crr = q.top(); q.pop();

                if (Find(crr.src.id) != Find(crr.dst.id))
                {
                        Union(crr.src.id, crr.dst.id);
                        ++count;
                        result += crr.weight;
                }
        }

        result = std::round(result * 100) / 100;
        std::cout << std::fixed << std::setprecision(2) << result << "\n";

        return 0;
}