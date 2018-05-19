#include <iostream>
#include <math.h>

unsigned int c, t;

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin >> c >> t;
        unsigned long long maxInstructions = t / 0.01;
        
        unsigned long long start = 0;
        unsigned long long end = maxInstructions;

        unsigned long long sol;
        while (start <= end)
        {
                unsigned long long middle = (start + end) / 2;
                double operations = c * middle * log2(middle);
                if (operations / 100 <= t)
                {
                        sol = middle;
                        start = middle + 1;
                }
                else
                {
                        end = middle - 1;
                }
        }

        std::cout << sol << "\n";

    return 0;
}