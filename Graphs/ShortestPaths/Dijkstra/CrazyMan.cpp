#include <iostream>
#include <vector>
#include <queue>
#include <bitset>

int coeff[21];
unsigned short degree;
int maxY;
unsigned int n, m;

unsigned long long distances[100000];
unsigned long long MAX = 2000000000000;
std::bitset<100000> visited;

struct Point
{
        int x, y;
};

struct Edge
{
        unsigned int dest;
        unsigned int weight;
};

std::vector<std::vector<Edge>> graph;
std::vector<Point> coordinates;

int CalcPolynom(int x)
{
        long long result = coeff[0];
        for (size_t i = 1; i <= degree; i++)
        {
                result = ((result * (x % maxY)) % maxY + coeff[i]) % maxY;
        }

        if (result < 0)
        {
                result += maxY;
        }

        return result;
}

struct DijkstraNode
{
        unsigned int node;
        unsigned long long distance;

        bool operator<(const DijkstraNode &other) const
        {
                return distance > other.distance;
        }
};

void Dijkstra()
{
        std::priority_queue<DijkstraNode> q;
        for (size_t i = 0; i < n; i++)
        {
                distances[i] = MAX;
        }

        distances[0] = 0;
        q.push({ 0, 0 });
        while (!q.empty())
        {
                DijkstraNode crr = q.top(); q.pop();
                if (visited.test(crr.node) == false)
                {
                        visited.set(crr.node);

                        std::vector<Edge> &edges = graph[crr.node];
                        for (size_t i = 0; i < edges.size(); i++)
                        {
                                unsigned long long alt = distances[crr.node] + edges[i].weight;
                                if (alt < distances[edges[i].dest])
                                {
                                        distances[edges[i].dest] = alt;
                                        q.push({ edges[i].dest, alt });
                                }
                        }
                }
        }
}

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin >> n >> m >> degree >> maxY;
        graph.assign(n, std::vector<Edge>());
        coordinates.assign(n, { 0, 0 });

        for (size_t i = 0; i < degree + 1; i++)
        {
                std::cin >> coeff[i];
        }

        int x;
        for (size_t i = 0; i < n; i++)
        {
                std::cin >> x;
                int y = CalcPolynom(x);

                coordinates[i] = { x, y };
        }

        unsigned int src, dst, distance;
        for (size_t i = 0; i < m; i++)
        {
                std::cin >> src >> dst;

                distance = std::abs(coordinates[src].x - coordinates[dst].x) + std::abs(coordinates[src].y - coordinates[dst].y);
                graph[src].push_back({ dst, distance });
                graph[dst].push_back({ src, distance });
        }

        Dijkstra();

        for (size_t i = 0; i < n - 1; i++)
        {
                if (distances[i] == MAX)
                {
                        std::cout << -1;
                }
                else
                {
                        std::cout << distances[i];
                }
                std::cout << " ";
        }
        std::cout << (distances[n - 1] == MAX ? -1 : distances[n - 1]) << '\n';

    return 0;
}