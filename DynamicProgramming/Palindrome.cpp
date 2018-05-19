// Task: Find the maximum palindrome subsequence of the input string.
// Memoization approach is used below.

#include <iostream>
#include <algorithm>
#include <cstring>

char text[3501];
int m[3500][3500];

int MaxPalindrome(int start, int end)
{
        if (start > end)
        {
                return 0;
        }

        if (start == end)
        {
                return 1;
        }

        if (text[start] == text[end] && start + 1 == end)
        {
                m[start][end] = 2;

                return 2;
        }

        if (text[start] == text[end])
        {
                if (m[start + 1][end - 1] == -1)
                {
                        m[start + 1][end - 1] = MaxPalindrome(start + 1, end - 1);
                }
                return m[start + 1][end - 1] + 2;
        }

        if (m[start + 1][end] == -1)
        {
                m[start + 1][end] = MaxPalindrome(start + 1, end);
        }
        if (m[start][end - 1] == -1)
        {
                m[start][end - 1] = MaxPalindrome(start, end - 1);
        }

        return std::max(m[start + 1][end], m[start][end - 1]);
}

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin.getline(text, 3501);

        for (size_t i = 0; i < std::strlen(text); i++)
        {
                for (size_t j = 0; j < std::strlen(text); j++)
                {
                        m[i][j] = -1;
                }
        }

        unsigned int result = MaxPalindrome(0, std::strlen(text) - 1);
        std::cout << result << '\n';

    return 0;
}