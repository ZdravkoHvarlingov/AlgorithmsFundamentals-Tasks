// There are N tasks and each of them has a starting time and duration.
// Task: Find the maximum number of tasks that you can perform.
// You can NOT do two or more tasks at the same time.
// If one task finishes at time X and another one starts at the same time X -> you can perform both of them.

#include <iostream>
#include <algorithm>

struct Task
{
        unsigned int startTime;
        unsigned int finishTime;
};

Task tasks[1000000];

int main()
{
        std::ios::sync_with_stdio(false);

        unsigned int start, length;
        std::cin >> start >> length;

        unsigned int i = 0;
        while (!std::cin.eof())
        {
                tasks[i++] = { start, start + length };

                std::cin >> start >> length;
        }

        std::qsort(tasks, i, sizeof(Task), [](const void *a, const void *b)
        {
                return (int)((Task*)a)->finishTime - (int)((Task*)b)->finishTime;
        });

        unsigned int n = i;
        i = 0;
        unsigned int count = 1;
        for (size_t j = 1; j < n; j++)
        {
                if (tasks[j].startTime >= tasks[i].finishTime)
                {
                        ++count;
                        i = j;
                }
        }

        if (n == 0)
        {
                std::cout << 0 << '\n';
        }
        else std::cout << count << '\n';

    return 0;
}