// There are N cups and each cup has some amount of strawberries. For each strawberry in the input - find the cup in which the stawberry is.
// Stawberies are numbered. For example if cup 1 has 5 stawberries - the stawberries in this cup are numbered from 1 to 5.

#include <iostream>

unsigned int cups[100000] = { 0 };
unsigned int strawberries[100000];
int n, m;

int main()
{
        std::ios::sync_with_stdio(false);
        
        std::cin >> n;
        for (size_t i = 0; i < n; i++)
        {
                std::cin >> cups[i];
        }

        std::cin >> m;
        for (size_t i = 0; i < m; i++)
        {
                std::cin >> strawberries[i];
        }

        for (size_t i = 1; i < n; i++)
        {
                cups[i] += cups[i - 1];
        }

        for (size_t i = 0; i < m; i++)
        {
                unsigned int crr = strawberries[i];
                int start = 0;
                int end = n - 1;

                int result = -1;
                while (start <= end)
                {
                        int middle = (start + end) / 2;
                        if (cups[middle] == crr)
                        {
                                result = middle;
                                break;
                        }
                        else if (cups[middle] > crr)
                        {
                                result = middle;
                                end = middle - 1;
                        }
                        else
                        {
                                start = middle + 1;
                        }
                }

                std::cout << result + 1 << "\n";
        }

    return 0;
}