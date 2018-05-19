// There is an input string. Using its letters (cutting them) find the number of banners you can make with the word BAZINGA.
// There is no case sensitivity, so Bazinga, BAZINGA, BaZiNgA, BAZINga, ... etc are valid banners.

#include <iostream>
#include <string>

unsigned int count[26] = { 0 };

bool IsNonCapital(char s)
{
        return s >= 'a' && s <= 'z';
}

bool IsCapital(char s)
{
        return s >= 'A' && s <= 'Z';
}

int main()
{
        std::ios::sync_with_stdio(false);

        std::string text;
        text.reserve(50000);
        std::string line;

        while (std::getline(std::cin, line))
        {
                text.append(line);
        }

        for (size_t i = 0; i < text.size(); i++)
        {
                if (IsNonCapital(text[i]))
                {
                        ++count[text[i] - 'a'];
                }
                else if (IsCapital(text[i]))
                {
                        ++count[text[i] - 'A'];
                }
        }

        std::string bazinga = "bazinga";
        count[0] /= 2;
        unsigned int min = count['b' - 'a'];
        for (size_t i = 1; i < bazinga.size(); i++)
        {
                if (count[bazinga[i] - 'a'] < min)
                {
                        min = count[bazinga[i] - 'a'];
                }
        }

        std::cout << min << "\n";

        return 0;
}