// Basic binary search

#include <iostream>

char names [100000][16];
unsigned int amount[100000];
int numbers[100000];
int n, m;

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin >> n >> m;

        for (size_t i = 0; i < n; i++)
        {
                std::cin >> names[i];
                std::cin >> amount[i];
        }

        for (size_t i = 1; i < n; i++)
        {
                amount[i] = amount[i] + amount[i - 1];
        }

        for (size_t i = 0; i < m; i++)
        {
                std::cin >> numbers[i];
        }

        for (size_t i = 0; i < m; i++)
        {
                int number = numbers[i];

                int start = 0;
                int end = n - 1;
                
                int result = -1;
                while (start <= end)
                {
                        int middle = (start + end) / 2;
                        if (amount[middle] == number)
                        {
                                result = middle;
                                break;
                        }
                        else if (amount[middle] > number)
                        {
                                result = middle;
                                end = middle - 1;
                        }
                        else
                        {
                                start = middle + 1;
                        }
                }

                std::cout << names[result] << "\n";
        }

    return 0;
}