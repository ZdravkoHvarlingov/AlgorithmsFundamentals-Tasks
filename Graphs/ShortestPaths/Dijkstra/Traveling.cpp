// Task: Find the shortest path between node X and node Y in directed weighted graph.

#include <vector>
#include <iostream>
#include <bitset>
#include <queue>

std::bitset<50000> visited;
unsigned int distance[50000];
int parent[50000];
unsigned int MAX = 4000000000;

struct Edge
{
        unsigned int weight;
        unsigned int dest;
};

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

int DijkstraShortestPath(unsigned int x, unsigned int y, int n, std::vector<Node> &nodes)
{
        visited.flip();
        for (size_t i = 0; i < n; i++)
        {
                visited.flip(i);
        }

        std::priority_queue<Pair, std::vector<Pair>, Comparator> q;
        for (size_t i = 0; i < x; i++)
        {
                distance[i] = MAX;
                parent[i] = -1;
                q.push({ i, MAX });
        }

        for (size_t i = x + 1; i < n; i++)
        {
                distance[i] = MAX;
                parent[i] = -1;
                q.push({ i, MAX });
        }

        distance[x] = 0;
        q.push({ x, 0 });

        while (!visited.all())
        {
                Pair node = q.top(); q.pop();
                if (!visited.test(node.node))
                {
                        visited.set(node.node);

                        if (distance[node.node] == MAX || node.node == y)
                        {
                                return distance[y] == MAX ? -1 : distance[y];
                        }

                        std::vector<Edge> &edges = nodes[node.node].edges;
                        for (size_t i = 0; i < edges.size(); i++)
                        {
                                if (distance[node.node] + edges[i].weight < distance[edges[i].dest])
                                {
                                        distance[edges[i].dest] = distance[node.node] + edges[i].weight;
                                        parent[edges[i].dest] = node.node;
                                        q.push({ edges[i].dest, distance[edges[i].dest] });
                                }
                        }
                }
        }

        return distance[y];
}

int main()
{
        int n, m, x, y;
        std::cin >> n >> m >> x >> y;
        --x;
        --y;
        std::vector<Node> nodes;
        nodes.assign(n, Node());

        unsigned int src, dest, weight;
        for (size_t i = 0; i < m; i++)
        {
                std::cin >> src >> dest >> weight;

                --src;
                --dest;
                nodes[src].edges.push_back({ weight, dest });
                nodes[dest].edges.push_back({ weight, src });
        }

        std::cout << DijkstraShortestPath(x, y, n, nodes) << "\n";

        return 0;
}