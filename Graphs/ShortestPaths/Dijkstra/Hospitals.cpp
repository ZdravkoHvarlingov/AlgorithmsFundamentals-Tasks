#include <vector>
#include <iostream>
#include <bitset>
#include <queue>

struct Edge;

unsigned int distances[10000];
unsigned int prev[10000];
std::bitset<10000> visited;
unsigned int MAX = 200000;
unsigned int n, m, h;
unsigned int hospitals[100];
std::vector<std::vector<Edge>> graph;

struct Pair
{
        unsigned int id;
        unsigned long long distance;
};

struct Edge
{
        unsigned int dest;
        unsigned int weight;
};

struct Comparator
{
        bool operator()(const Pair &first, const Pair &second) const
        {
                if (first.distance == second.distance)
                {
                        return first.id > second.id;
                }
                return first.distance > second.distance;
        }
};

void DijkstraShortestPath(unsigned int start)
{
        visited.reset();
        visited.flip();
        std::priority_queue<Pair, std::vector<Pair>, Comparator> q;

        for (size_t i = 0; i < n; i++)
        {
                prev[i] = -1;
                distances[i] = MAX;
                visited.set(i, false);
        }

        distances[start] = 0;
        q.push({ start, 0 });

        while (!visited.all())
        {
                Pair node = q.top(); q.pop();
                if (!visited.test(node.id));
                {
                        visited.set(node.id, true);

                        std::vector<Edge> &edges = graph[node.id];

                        for (const Edge &edg : edges)
                        {
                                unsigned int alt = distances[node.id] + edg.weight;
                                if (alt < distances[edg.dest])
                                {
                                        distances[edg.dest] = alt;
                                        q.push({ edg.dest, alt });

                                        prev[edg.dest] = node.id;
                                }
                        }
                }
        }
}

int main()
{
        std::cin >> n >> m >> h;
        graph.assign(n, std::vector<Edge>());

        unsigned int src, dest, weight;
        for (size_t i = 0; i < h; i++)
        {
                std::cin >> hospitals[i];
                --hospitals[i];
        }

        for (size_t i = 0; i < m; i++)
        {
                std::cin >> src >> dest >> weight;

                --src;
                --dest;
                graph[src].push_back({ dest, weight });
                graph[dest].push_back({ src, weight });
        }

        int result = -1;

        for (size_t i = 0; i < h; i++)
        {
                DijkstraShortestPath(hospitals[i]);
                
                int sum = 0;
                for (size_t j = 0; j < n; j++)
                {
                        sum += distances[j];
                }
                for (size_t j = 0; j < h; j++)
                {
                        sum -= distances[hospitals[j]];
                }

                if (result == -1 || sum < result)
                {
                        result = sum;
                }
        }

        std::cout << result << "\n";

        return 0;
}