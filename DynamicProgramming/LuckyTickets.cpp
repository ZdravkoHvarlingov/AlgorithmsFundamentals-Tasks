// Task: Find the number of lucky tickets with 2N digits and sum of the digits S. 
// Lucky ticket is a one that has a sum of the first N digits equal to the sum of the last N.
// The ticket is able to have a leading 0.


#include <iostream>

short n, s;
unsigned long long dp[51][501];

int main()
{
        std::cin >> n >> s;

        if (s % 2 != 0)
        {
                std::cout << 0 << '\n';

                return 0;
        }

        s /= 2;
        for (size_t i = 1; i <= s; i++)
        {
                dp[0][i] = 0;
        }
        for (size_t i = 0; i <= n; i++)
        {
                dp[i][0] = 1;
        }

        for (short l = 1; l <= n; l++)
        {
                for (short sum = 1; sum <= s; sum++)
                {
                        dp[l][sum] = 0;
                        for (short d = 0; d <= 9; d++)
                        {
                                if (sum - d >= 0)
                                {       
                                        dp[l][sum] += dp[l - 1][sum - d];
                                }
                        }

                        dp[l][sum] %= 5741;
                }
        }

        unsigned long long result = (dp[n][s] * dp[n][s]) % 5741;

        std::cout << result << '\n';

    return 0;
}