#include <vector>
#include <iostream>
#include <bitset>
#include <queue>

struct Edge;

unsigned long long distances[500000];
unsigned int prev[500000];
bool isTrainPath[500000];
std::bitset<500000> visited;
unsigned long long MAX = 1000000000000000;
unsigned int n, m, k;
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
        bool train;
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

void DijkstraShortestPath()
{
        visited.flip();
        std::priority_queue<Pair, std::vector<Pair>, Comparator> q;

        for (size_t i = 0; i < n; i++)
        {
                prev[i] = -1;
                isTrainPath[i] = 0;
                distances[i] = MAX;
                visited.set(i, false);
        }

        distances[0] = 0;
        q.push({ 0, 0 });

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
                                if (alt < distances[edg.dest] || (alt == distances[edg.dest] && edg.train == false))
                                {
                                        distances[edg.dest] = alt;
                                        q.push({ edg.dest, alt });

                                        prev[edg.dest] = node.id;
                                        isTrainPath[edg.dest] = edg.train ? 1 : 0;
                                }
                        }
                }
        }
}

int main()
{
        std::cin >> n >> m >> k;
        graph.assign(n, std::vector<Edge>());

        unsigned int src, dest, weight;
        for (size_t i = 0; i < m; i++)
        {
                std::cin >> src >> dest >> weight;

                --src;
                --dest;
                graph[src].push_back({ dest, weight, false });
                graph[dest].push_back({ src, weight, false });
        }

        for (size_t i = 0; i < k; i++)
        {
                std::cin >> dest >> weight;
                --dest;

                graph[0].push_back({ dest, weight, true });
                graph[dest].push_back({ 0, weight, true });
        }

        DijkstraShortestPath();

        unsigned int result = k;
        for (size_t i = 0; i < n; i++)
        {
                if (prev[i] != - 1 && isTrainPath[i])
                {
                        --result;
                }
        }

        std::cout << result << "\n";

        return 0;
}