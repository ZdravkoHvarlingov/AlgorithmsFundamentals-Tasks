// Task: Find the cycle with a number of vertices at least 4 which has a minimum total weight.


#include <vector>
#include <iostream>
#include <bitset>
#include <queue>

unsigned int distances[300];
unsigned int count[300];
unsigned int MAX = 1500000;
int parent[300];

std::bitset<300> visited;

unsigned int n, m;
int result;

struct Edge
{
        unsigned int dest;
        unsigned int weight;
};

std::vector<std::vector<Edge>> graph;

struct Node
{
        unsigned int id;
        unsigned int distance;

        bool operator<(const Node &other) const
        {
                return distance > other.distance;
        }
};

bool IsValidCycle(int fstNode, int sndNode)
{
        unsigned int diff;
        if (count[fstNode] > count[sndNode])
        {
                diff = count[fstNode] - count[sndNode];
                for (size_t i = 0; i < diff; i++)
                {
                        fstNode = parent[fstNode];
                }
        }
        else if (count[sndNode] > count[fstNode])
        {
                diff = count[sndNode] - count[fstNode];
                for (size_t i = 0; i < diff; i++)
                {
                        sndNode = parent[sndNode];
                }
        }

        while (sndNode != fstNode)
        {
                sndNode = parent[sndNode];
                fstNode = parent[fstNode];
        }

        return parent[fstNode] == -1;
}

void Dijkstra(unsigned int node)
{
        std::priority_queue<Node> q;
        for (size_t i = 0; i < n; i++)
        {
                distances[i] = MAX;
                parent[i] = -1;
                count[i] = 0;
                q.push({ i, MAX });
                visited.set(i, false);
        }

        distances[node] = 0;
        q.push({ node, 0 });

        while (!q.empty())
        {
                Node crr = q.top(); q.pop();
                if (visited.test(crr.id) == false)
                {
                        visited.set(crr.id);

                        if (crr.distance == MAX)
                        {
                                break;
                        }

                        std::vector<Edge> &edges = graph[crr.id];
                        for (size_t i = 0; i < edges.size(); i++)
                        {
                                unsigned int alt = distances[crr.id] + edges[i].weight;
                                if (visited.test(edges[i].dest) == false && alt < distances[edges[i].dest])
                                {
                                        distances[edges[i].dest] = alt;
                                        parent[edges[i].dest] = crr.id;
                                        count[edges[i].dest] = count[crr.id] + 1;

                                        q.push({ edges[i].dest, alt });
                                }
                                else if (visited.test(edges[i].dest))
                                {
                                        unsigned int cycleLength = distances[edges[i].dest] + distances[crr.id] + edges[i].weight;
                                        if (count[edges[i].dest] + count[crr.id] + 1 >= 3
                                                && cycleLength < result && IsValidCycle(crr.id, edges[i].dest))
                                        {
                                                result = cycleLength;
                                        }
                                }
                        }
                }
        }
}

int main()
{
        std::cin >> n >> m;
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

        result = MAX;
        for (size_t i = 0; i < n; i++)
        {
                Dijkstra(i);
        }

        if (result == MAX)
        {
                std::cout << -1 << "\n";
        }
        else std::cout << result << "\n";
}