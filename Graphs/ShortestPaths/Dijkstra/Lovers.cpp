// You are given N bus stops and M edges, representing a bus line.
// There are N times - the time needed for a bus to come to that specific bus stop (starting from 0).
// Task: Find the minimum time needed in order to travel from bus stop 0 to bus stop N - 1.

#include <vector>
#include <iostream>
#include <bitset>
#include <queue>

std::bitset<10000> visited;
unsigned int distance[10000];
unsigned int times[10000];
int parent[10000];
unsigned int MAX = 20000000;

unsigned int order[10000] = { 0 };

struct Edge
{
        unsigned int dest;
        unsigned int weight;
};

std::vector<std::vector<Edge>> graph;

unsigned int n, m;

struct Node
{
        std::vector<Edge> edges;
};

struct Pair
{
        unsigned int node;
        unsigned int distance;
};

struct Comparator
{
        bool operator()(const Pair &first, const Pair &second)
        {
                return first.distance > second.distance;
        }
};

void DijkstraShortestPath()
{
        std::priority_queue<Pair, std::vector<Pair>, Comparator> q;
        for (size_t i = 0; i < n; i++)
        {
                distance[i] = MAX;
                parent[i] = -1;
        }

        distance[0] = 0;
        q.push({ 0, 0 });

        while (!q.empty())
        {
                Pair crr = q.top(); q.pop();
                if (!visited.test(crr.node))
                {
                        visited.set(crr.node);

                        if (distance[crr.node] == MAX || crr.node == n - 1)
                        {
                                return;
                        }

                        std::vector<Edge> &edges = graph[crr.node];
                        for (size_t i = 0; i < edges.size(); i++)
                        {
                                unsigned alt = distance[crr.node];
                                unsigned int timeToWait = times[crr.node] - alt % times[crr.node];
                                timeToWait = timeToWait == times[crr.node] ? 0 : timeToWait;
                                alt += timeToWait + edges[i].weight;

                                if (alt < distance[edges[i].dest])
                                {
                                        distance[edges[i].dest] = alt;
                                        parent[edges[i].dest] = crr.node;
                                        q.push({ edges[i].dest, alt });
                                }
                        }
                }
        }
}

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin >> n >> m;
        graph.assign(n, std::vector<Edge>());

        for (size_t i = 0; i < n; i++)
        {
                std::cin >> times[i];
        }

        unsigned int src, dest, weight;
        for (size_t i = 0; i < m; i++)
        {
                std::cin >> src >> dest >> weight;

                graph[src].push_back({ dest, weight });
        }

        DijkstraShortestPath();

        unsigned int count = 0;
        int crrNode = n - 1;
        while (crrNode != -1)
        {
                order[count] = crrNode;
                ++count;

                crrNode = parent[crrNode];
        }

        if (distance[n - 1] != MAX)
        {
                std::cout << distance[n - 1] << '\n';
                std::cout << count << '\n';
                for (size_t i = count - 1; i > 0; --i)
                {
                        std::cout << order[i] << " ";
                }
                std::cout << order[0] << '\n';
        }
        else std::cout << -1 << '\n';

        return 0;
}