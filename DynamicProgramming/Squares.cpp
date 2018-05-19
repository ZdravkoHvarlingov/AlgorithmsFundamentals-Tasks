// Task: Find the minimum number of squares with sum N.

#include <iostream>
#include <math.h>
#include <algorithm>

unsigned int n, maxSquare;
unsigned int mins[60001];

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin >> n;
        mins[0] = 0;
        mins[1] = 1;

        for (size_t i = 2; i <= n; i++)
        {
                mins[i] = mins[i - 1] + 1;
                maxSquare = sqrt(i);

                for (size_t s = 2; s <= maxSquare; s++)
                {
                        unsigned int crr = mins[i - s * s] + 1;
                        mins[i] = std::min(mins[i], crr);
                }
        }

        std::cout << mins[n] << '\n';

    return 0;
}