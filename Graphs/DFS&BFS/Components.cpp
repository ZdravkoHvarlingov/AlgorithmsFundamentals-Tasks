// Number of components in an undirected graph.

#include <iostream>
#include <bitset>

bool graph[500][500] = { 0 };

void DFS(std::bitset<500> &visited, int crrNode, int n)
{
        for (size_t i = 0; i < n; i++)
        {
                if (graph[crrNode][i] && visited.test(i) == false)
                {
                        visited.set(i);
                        DFS(visited, i, n);
                }
        }
}

int GetComponents(int n)
{
        std::bitset<500> visited;
        visited.flip();
        for (size_t i = 0; i < n; i++)
        {
                visited.set(i, false);
        }
        int components = 0;
        while (!visited.all())
        {
                int ind = 0;
                while (ind < n && visited.test(ind) == true)
                {
                        ++ind;
                }
                visited.set(ind);
                DFS(visited, ind, n);

                ++components;
        }

        return components;
}

int main()
{
        int n = 1;
        scanf("%d", &n);
        int m = 1;
        scanf("%d", &m);

        int left, right;
        for (size_t i = 0; i < m; i++)
        {
                scanf("%d", &left);
                scanf("%d", &right);

                graph[left - 1][right - 1] = true;
                graph[right - 1][left - 1] = true;
        }

        int components = GetComponents(n);
        printf("%d\n", components);

        return 0;
}