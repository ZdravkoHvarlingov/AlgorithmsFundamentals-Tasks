#include <iostream>
#include <queue>

int start;
int end;
bool u[1000007] = { false };

int Reverse(int number)
{
        int result = 0;

        while (number != 0)
        {
                result *= 10;
                result += number % 10;

                number /= 10;
        }

        return result;
}

int MakeBFS()
{
        int SENTINEL = 10000000;

        std::queue<int> q;
        int level = 0;
        q.push(start);
        q.push(SENTINEL);

        while (!q.empty())
        {
                int crr = q.front();
                q.pop();

                if (crr == SENTINEL)
                {
                        ++level;
                        q.push(SENTINEL);
                }
                else
                {
                        if (crr == end)
                        {
                                return level + 1;
                        }

                        int first = (crr + 1) % 1000007;
                        int second = Reverse(crr) % 1000007;

                        if (!u[first])
                        {
                                q.push(first);
                                u[first] = true;
                        }
                        if (!u[second])
                        {
                                q.push(second);
                                u[second] = true;
                        }
                }
        }

        return level;
}

int main()
{
        std::cin >> start;
        std::cin >> end;

        std::cout << MakeBFS() << "\n";

        return 0;
}