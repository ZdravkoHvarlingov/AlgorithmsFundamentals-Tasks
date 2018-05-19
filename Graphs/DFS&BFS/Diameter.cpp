#include <iostream>
#include <bitset>
// Task: Find longest path in a undirected graph, which is a tree.


short graph[1000][1000];
std::bitset<1000> visited;
unsigned int n;
unsigned int maxLength;
unsigned int maxNode;

void MakeDFS(unsigned short crrNode, unsigned int crrLength)
{
        if (crrLength > maxLength)
        {
                maxLength = crrLength;
                maxNode = crrNode;
        }

        for (size_t i = 0; i < n; i++)
        {
                if (graph[crrNode][i] != -1 && visited.test(i) == false)
                {
                        visited.set(i);
                        MakeDFS(i, crrLength + graph[crrNode][i]);
                        visited.set(i, false);
                }
        }
}

void FindLongest()
{
        maxLength = 0;
        maxNode = 0;
        
        visited.set(0);
        MakeDFS(0, 0);
        visited.set(0, false);

        visited.set(maxNode);
        MakeDFS(maxNode, 0);
}

int main()
{
        for (size_t i = 0; i < 1000; i++)
        {
                for (size_t j = 0; j < 1000; j++)
                {
                        graph[i][j] = -1;
                }
        }

        std::cin >> n;
        char c;
        short left, right;
        for (size_t i = 0; i < n - 1; i++)
        {
                std::cin >> left;
                std::cin >> right;
                --left;
                --right;

                std::cin >> graph[left][right];
                graph[right][left] = graph[left][right];
        }

        FindLongest();
        std::cout << maxLength << "\n";

        return 0;
}