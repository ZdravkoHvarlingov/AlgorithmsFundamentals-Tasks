// Using binary search on the answer.

#include <iostream>

bool IsSolution(int d, unsigned int pipes[10000], int n, int k)
{
        unsigned long long result = 0;
        for (size_t i = 0; i < n; i++)
        {
                result += pipes[i] / d;
        }

        return result >= k;
}

int main()
{
        unsigned int t = 1;
        scanf("%u", &t);

        unsigned int n = 1;
        scanf("%u", &n);
        
        unsigned int k = 1;
        scanf("%u", &k);

        unsigned int pipes[10000];
        unsigned long long max = 0;
        
        for (size_t i = 0; i < t; i++)
        {
                max = 0;
                for (size_t j = 0; j < n; j++)
                {
                        unsigned int length = 1;
                        scanf("%u", &length);
                        pipes[j] = length;

                        if (max < length)
                        {
                                max = length;
                        }
                }

                int start = 1;
                int end = max;
                unsigned int answer = 0;
                while (start <= end)
                {
                        int middle = (start + end) / 2;
                        if (IsSolution(middle, pipes, n, k))
                        {
                                start = middle + 1;
                                answer = middle;
                        }
                        else
                        {
                                end = middle - 1;
                        }
                }

                printf("%u\n", answer);

                if (i < t - 1)
                {
                        scanf("%u", &n);
                        scanf("%u", &k);
                }
        }

        return 0;
}