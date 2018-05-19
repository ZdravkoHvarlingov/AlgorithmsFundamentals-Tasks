// Task: You have N students and an exam.
// M couples that can talk to each other safely and K couples that can NOT talk safely.
// The tasks is to find minimum number of dangerous talkings so the information can arrive from student with index 0 to student with index N - 1

#include <vector>
#include <iostream>
#include <bitset>
#include <queue>

struct Edge;

unsigned int distances[10000];
unsigned int prev[10000];
std::bitset<10000> visited;
unsigned int MAX = 200000;
unsigned int n, m, k;
std::vector<std::vector<Edge>> graph;

struct Pair
{
        unsigned int id;
        unsigned int distance;
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

int DijkstraShortestPath()
{
        visited.reset();
        visited.flip();
        std::priority_queue<Pair, std::vector<Pair>, Comparator> q;

        for (size_t i = 0; i < n; i++)
        {
                prev[i] = -1;
                distances[i] = MAX;
                visited.set(i, false);

                q.push({ i, MAX });
        }

        distances[n - 1] = 0;
        q.push({ n - 1, 0 });

        while (!visited.all())
        {
                Pair node = q.top(); q.pop();
                if (!visited.test(node.id));
                {
                        visited.set(node.id, true);

                        if (node.id == 0)
                        {
                                return distances[0] == MAX ? -1 : distances[0];
                        }

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

        return distances[0] == MAX ? -1 : distances[0];
}

int main()
{
        std::cin >> n >> m >> k;
        graph.assign(n, std::vector<Edge>());

        unsigned int src, dest;

        for (size_t i = 0; i < m; i++)
        {
                std::cin >> src >> dest;

                if (src >= 0 && src < n && dest >= 0 && dest < n)
                {
                        graph[src].push_back({ dest, 0 });
                        graph[dest].push_back({ src, 0 });
                }
        }

        for (size_t i = 0; i < k; i++)
        {
                std::cin >> src >> dest;

                if (src >= 0 && src < n && dest >= 0 && dest < n)
                {
                        graph[src].push_back({ dest, 1 });
                        graph[dest].push_back({ src, 1 });
                }
        }

        std::cout << DijkstraShortestPath() << "\n";

        return 0;
}