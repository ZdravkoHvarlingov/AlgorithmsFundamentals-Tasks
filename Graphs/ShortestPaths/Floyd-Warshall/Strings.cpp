// Task: Find the minimum price required to make the first and second string EQUAL.
// Each char swap requires a specific price and there are only specific chars swaps.

// Example input:
// uayd
// uxxd
// 3
// a x 8
// x y 13
// d c 3

// Example output: 21 (swap a -> x and x -> y, so 8 + 13 = 21)

#include <iostream>
#include <string.h>
#include <algorithm>

unsigned int distances[30][30];
unsigned int MAX = 150000;

char first[15000];
char second[15000];

unsigned int n;

int main()
{
        std::cin.getline(first, 15000);
        std::cin.getline(second, 15000);
        if (strlen(first) > 10000)
        {
                first[10000] = '\0';
        }
        if (strlen(second) > 10000)
        {
                second[10000] = '\0';
        }
        std::cin >> n;

        for (size_t i = 0; i < 26; i++)
        {
                for (size_t j = 0; j < 26; j++)
                {
                        distances[i][j] = MAX;
                }
        }

        for (size_t i = 0; i < 26; i++)
        {
                distances[i][i] = 0;
        }

        char fst, snd;
        unsigned int weight;
        for (size_t i = 0; i < n; i++)
        {
                std::cin >> fst >> snd >> weight;
                fst = fst - 'a';
                snd = snd - 'a';

                distances[fst][snd] = std::min(weight, distances[fst][snd]);
                distances[snd][fst] = std::min(weight, distances[snd][fst]); //  -     ,    
        }

        if (strlen(first) != strlen(second))
        {
                std::cout << -1 << '\n';
        }
        else
        {
                for (size_t k = 0; k < 26; k++)
                {
                        for (size_t i = 0; i < 26; i++)
                        {
                                for (size_t j = 0; j < 26; j++)
                                {
                                        unsigned int alt = distances[i][k] + distances[k][j];
                                        if (distances[i][j] > alt)
                                        {
                                                distances[i][j] = alt;
                                        }
                                }
                        }
                }

                unsigned int result = 0;
                bool hasSolution = true;
                for (size_t i = 0; i < strlen(first); i++)
                {
                        unsigned int min = MAX;
                        for (size_t j = 0; j < 26; j++)
                        {
                                unsigned int alt = distances[first[i] - 'a'][j] + distances[second[i] - 'a'][j];
                                if (alt < min)
                                {
                                        min = alt;
                                }
                        }
                        if (min == MAX)
                        {
                                hasSolution = false;
                                break;
                        }
                        result += min;
                }

                if (hasSolution)
                {
                        std::cout << result << '\n';
                }
                else std::cout << -1 << '\n';
        }
        
    return 0;
}