// Task: Find the number of shortest paths mod 1000000007 from a given source node to all other nodes.

#include <vector>
#include <iostream>
#include <bitset>
#include <queue>

struct Edge;

unsigned long long distances[100000];
unsigned long long mins[100000] = { 0 };
std::bitset<100000> visited;
unsigned long long MAX = 2000000000000000;
unsigned int n, m;
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

std::pair<long long, unsigned long long> DijkstraShortestPath()
{
        visited.reset();
        visited.flip();
        std::priority_queue<Pair, std::vector<Pair>, Comparator> q;

        for (size_t i = 0; i < n; i++)
        {
                distances[i] = MAX;
                visited.set(i, false);
                mins[i] = 0;

                q.push({ i, MAX });
        }

        distances[0] = 0;
        q.push({ 0, 0 });
        mins[0] = 1;

        while (!visited.all())
        {
                Pair node = q.top(); q.pop();
                if (!visited.test(node.id))
                {
                        visited.set(node.id, true);
                        if (distances[node.id] == MAX)// || node.id == n - 1)
                        {
                                break;
                        }

                        std::vector<Edge> &edges = graph[node.id];

                        for (const Edge &edg : edges)
                        {
                                unsigned long long alt = distances[node.id] + edg.weight;

                                if (visited.test(edg.dest) == false && alt < distances[edg.dest])
                                {
                                        mins[edg.dest] = mins[node.id] % 1000000007;
                                        distances[edg.dest] = alt;
                                        q.push({ edg.dest, alt });
                                }
                                else if (visited.test(edg.dest) == false && alt == distances[edg.dest])
                                {
                                        mins[edg.dest] += mins[node.id];
                                        mins[edg.dest] %= 1000000007;
                                }
                        }
                }
        }

        if (distances[n - 1] == MAX)
        {
                return std::make_pair(-1, 0);
        }

        return std::make_pair(distances[n - 1], mins[n - 1]); //% 1000000007);
}

int main()
{
        std::ios_base::sync_with_stdio(false);

        std::cin >> n >> m;
        graph.assign(n, std::vector<Edge>());

        unsigned int src, dest, weight;

        for (size_t i = 0; i < m; i++)
        {
                std::cin >> src >> dest >> weight;
                --src;
                --dest;

                if (src >= 0 && src < n && dest >= 0 && dest < n)
                {
                        graph[src].push_back({ dest, weight });
                }
        }

        std::pair<long long, unsigned long long> result = DijkstraShortestPath();
        std::cout << result.first << " " << result.second << "\n";

        return 0;
}