// Task: You have N wires with a specific weight. 
// The job is to split the wires in two groups such that the difference between the sum of the wires in each group is MINIMUM.
// Each wire is NOT splittable.

#include <iostream>

short wires[300];
short n;

bool dp[301][150001];

int main()
{
        std::cin >> n;
        for (size_t i = 0; i < n; i++)
        {
                std::cin >> wires[i];
        }

        unsigned int sum = 0;
        for (size_t i = 0; i < n; i++)
        {
                sum += wires[i];
        }

        for (size_t i = 1; i <= sum; i++)
        {
                dp[0][i] = false;
        }
        for (size_t i = 1; i <= n; i++)
        {
                dp[i][0] = true;
        }

        for (size_t i = 1; i <= n; i++)
        {
                for (size_t j = 1; j <= sum; j++)
                {
                        dp[i][j] = dp[i - 1][j];

                        if (dp[i][j] == false && wires[i - 1] <= j && dp[i - 1][j - wires[i - 1]])
                        {
                                dp[i][j] = true;
                        }
                }
        }

        unsigned int diff = 1500000;
        for (size_t j = sum / 2; j >= 0; j--)
        {
                if (dp[n][j] == true)
                {
                        diff = (sum - 2 * j);
                        break;
                }
        }

        std::cout << diff << '\n';

    return 0;
}