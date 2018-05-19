// There are K different colors and one of them is BLUE for sure.
// Find the number of beads sequences of length N mod 1000000007, which do NOT have two BLUE neighbouring beads.
// Here is used memoization approach.

#include <iostream>

unsigned int n, k;

long long m[101];

unsigned int CalcN(unsigned int length)
{
        if (length <= 0)
        {
                return 1;
        }

        if (length == 1)
        {
                return k;
        }

        if (m[length - 2] == -1)
        {
                m[length - 2] = CalcN(length - 2) % 1000000007;
        }
        if (m[length - 1] == -1)
        {
                m[length - 1] = CalcN(length - 1) % 1000000007;
        }

        unsigned int startsWithBlue = ((k - 1) * m[length - 2]) % 1000000007;
        unsigned int startsWithNoBlue = ((k - 1) * m[length - 1]) % 1000000007;

        return (startsWithBlue + startsWithNoBlue) % 1000000007;
}

int main()
{
        std::cin >> n >> k;
        for (size_t i = 0; i <= n; i++)
        {
                m[i] = -1;
        }

        std::cout << CalcN(n) << '\n';

    return 0;
}