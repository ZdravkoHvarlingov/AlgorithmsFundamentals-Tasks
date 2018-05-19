// There is an undirected weighted graph with N nodes, and M edges. We have input three nodes:
// X - starting point, Y - intermediate point, Z - end point.
// Task: Find the shortest path from X to Z, which passes through Y.

#include <vector>
#include <iostream>
#include <bitset>
#include <queue>
#include <stack>

std::bitset<50000> visited;
unsigned int distance[50000];
int parent[50000];
unsigned int MAX = 600000000;

struct Edge
{
        unsigned int dest;
        unsigned int weight;
};

std::vector<std::vector<Edge>> graph;

unsigned int n, m, x, y, z;

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

void DijkstraShortestPath(unsigned int start, unsigned int end)
{
        std::priority_queue<Pair, std::vector<Pair>, Comparator> q;
        for (size_t i = 0; i < n; i++)
        {
                distance[i] = MAX;
                parent[i] = -1;

                visited.set(i, false);
        }

        distance[start] = 0;
        q.push({ start, 0 });

        while (!q.empty())
        {
                Pair crr = q.top(); q.pop();
                if (!visited.test(crr.node))
                {
                        visited.set(crr.node);

                        if (distance[crr.node] == MAX || crr.node == end)
                        {
                                return;
                        }

                        std::vector<Edge> &edges = graph[crr.node];
                        for (size_t i = 0; i < edges.size(); i++)
                        {
                                unsigned alt = distance[crr.node] + edges[i].weight;

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

        std::cin >> n >> m >> x >> y >> z;
        --x;
        --y;
        --z;
        graph.assign(n, std::vector<Edge>());

        unsigned int src, dest, weight;
        for (size_t i = 0; i < m; i++)
        {
                std::cin >> src >> dest >> weight;
                --src;
                --dest;

                graph[src].push_back({ dest, weight });
                graph[dest].push_back({ src, weight });
        }

        DijkstraShortestPath(x ,y);

        if (distance[y] == MAX)
        {
                std::cout << -1 << '\n';
                return 0;
        }

        unsigned int finalLength = distance[y];

        std::stack<unsigned int> path1;
        int crrNode = y;
        while (crrNode != -1)
        {
                path1.push(crrNode);

                crrNode = parent[crrNode];
        }

        DijkstraShortestPath(y, z);
        if (distance[z] == MAX)
        {
                std::cout << -1 << '\n';
                return 0;
        }
        finalLength += distance[z];
        std::cout << finalLength << '\n';

        crrNode = z;
        std::stack<unsigned int> path2;
        while (crrNode != -1)
        {
                path2.push(crrNode);

                crrNode = parent[crrNode];
        }
        
        while (!path1.empty())
        {
                std::cout << path1.top() + 1 << " ";
                path1.pop();
        }
        path2.pop();
        while (!path2.empty())
        {
                std::cout << path2.top() + 1 << " ";
                path2.pop();
        }

        std::cout << '\n';

        return 0;
}