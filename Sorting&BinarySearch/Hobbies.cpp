#include <iostream>

unsigned int hobbies[300000];
unsigned int temp[300000];
int n;

unsigned int FindMaxInversion(int start, int end)
{
        if (start >= end)
        {
                return 0;
        }

        int middle = (start + end) / 2;
        int max = FindMaxInversion(start, middle);
        int sMax = FindMaxInversion(middle + 1, end);

        if (sMax > max)
        {
                max = sMax;
        }

        int i = start;
        int j = middle + 1;
        int count = start;
        while (i <= middle && j <= end)
        {
                if (hobbies[i] <= hobbies[j])
                {
                        temp[count++] = hobbies[i];
                        ++i;
                }
                else if (hobbies[i] > hobbies[j])
                {
                        if (hobbies[j] > max) max = hobbies[j];
                        temp[count++] = hobbies[j];
                        ++j;
                }
        }

        while (i <= middle)
        {
                temp[count++] = hobbies[i];
                ++i;
        }
        while (j <= end)
        {
                temp[count++] = hobbies[j];
                ++j;
        }

        for (size_t ind = start; ind <= end; ind++)
        {
                hobbies[ind] = temp[ind];
        }

        return max;
}

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin >> n;
        for (size_t i = 0; i < n; i++)
        {
                std::cin >> hobbies[i];
        }

        unsigned int max = FindMaxInversion(0, n - 1);

        std::cout << max << "\n";

    return 0;
}