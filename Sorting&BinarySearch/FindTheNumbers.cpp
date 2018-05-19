// Task: There are N numbers in a sorted order and M pairs of numbers (A, B).
// For each pair find the amount of numbers greater or equal to A and less or equal to B.

#include <iostream>

int main()
{
        int numbers[100000];
        int results[10000];
        unsigned int n = 1;
        std::cin >> n;
        for (size_t i = 0; i < n; i++)
        {
                std::cin >> numbers[i];
        }

        unsigned int m = 1;
        std::cin >> m;

        for (size_t i = 0; i < m; i++)
        {
                int a = 1, b = 1;
                std::cin >> a >> b;

                int start = 0;
                int end = n - 1;
                int beginIndex = -1;
                while (start <= end)
                {
                        int middle = (start + end) / 2;
                        if (numbers[middle] >= a)
                        {
                                beginIndex = middle;
                                end = middle - 1;
                        }
                        else
                        {
                                start = middle + 1;
                        }
                }
                
                start = 0;
                end = n - 1;
                int endIndex = -1;
                while (start <= end)
                {
                        int middle = (start + end) / 2;
                        if (numbers[middle] <= b)
                        {
                                endIndex = middle;
                                start = middle + 1;
                        }
                        else
                        {
                                end = middle - 1;
                        }
                }

                if (beginIndex != -1 && endIndex != -1)
                {
                        results[i] = endIndex - beginIndex + 1;
                } 
                else
                {
                        results[i] = 0;
                }
        }

        for (size_t i = 0; i < m; i++)
        {
                std::cout << results[i] << std::endl;
        }

        return 0;
}