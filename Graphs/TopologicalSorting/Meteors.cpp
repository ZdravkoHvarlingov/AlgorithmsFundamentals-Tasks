// Task: Find the minimum finish time of each task.
// If two tasks are independent on each other => they can be performed at the same time.

#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<unsigned int>> graph;

unsigned int n, m;
unsigned int finalTimes[200000];
unsigned int timeNeeded[200000];
unsigned int inputDegree[200000];

int main()
{
        std::cin >> n;
        graph.assign(n, std::vector<unsigned int>());
        
        unsigned int src;
        for (size_t i = 0; i < n; i++)
        {
                std::cin >> timeNeeded[i];
                finalTimes[i] = timeNeeded[i];
                std::cin >> m;
                inputDegree[i] = m;
                for (size_t j = 0; j < m; j++)
                {
                        std::cin >> src;
                        graph[src].push_back(i);
                }
        }

        std::queue<unsigned int> q;
        for (size_t i = 0; i < n; i++)
        {
                if (inputDegree[i] == 0)
                {
                        q.push(i);
                }
        }

        while (!q.empty())
        {
                unsigned int crr = q.front(); q.pop();
                std::vector<unsigned int> &edges = graph[crr];

                for (size_t i = 0; i < edges.size(); i++)
                {
                        unsigned int dest = edges[i];
                        
                        if (finalTimes[crr] + timeNeeded[dest] > finalTimes[dest])
                        {
                                finalTimes[dest] = finalTimes[crr] + timeNeeded[dest];
                        }

                        --inputDegree[dest];
                        if (inputDegree[dest] == 0)
                        {
                                q.push(dest);
                        }
                }
        }

        for (size_t i = 0; i < n; i++)
        {
                std::cout << finalTimes[i] << '\n';
        }

    return 0;
}