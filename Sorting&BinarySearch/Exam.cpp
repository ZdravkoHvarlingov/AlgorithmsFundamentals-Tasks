#include <iostream>

unsigned long long n, f;

bool IsSolution(unsigned long long count)
{
        unsigned long long first = count * f;
        unsigned long long second = count * (count - 1);
		
		// Check for multiplication overflow
        if (count != 0 && second / count != count - 1)
        {
                return true;
        }
        second /= 2;

        unsigned long long sum = first + second;
		// Check for addition overflow
        if (sum < first)
        {
                return true;
        }

        return sum >= n;
}

int main()
{
        std::cin >> n >> f;

        unsigned long long start = 0;
        unsigned long long end = n / f + 1;
        unsigned long long result;

        while (start <= end)
        {
                unsigned long long middle = (start + end) / 2;

                if (IsSolution(middle))
                {
                        result = middle;
                        end = middle - 1;
                }
                else
                {
                        start = middle + 1;
                }
        }

        std::cout << result << "\n";

    return 0;
}