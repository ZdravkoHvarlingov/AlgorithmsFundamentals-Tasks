// Simple program which finds the number of inverses in a number sequence using MERGE SORT.


#include <vector>
#include <iostream>

unsigned long long MergeSortInverses(std::vector<uint32_t> &numbers, int start, int end)
{
        if (start >= end)
        {
                return 0;
        }

        int middle = (start + end) / 2;

        unsigned long long inverses = 0;
        inverses += MergeSortInverses(numbers, start, middle);
        inverses += MergeSortInverses(numbers, middle + 1, end);

        std::vector<uint32_t> sorted;
        sorted.reserve(end - start + 1);

        int first = start;
        int second = middle + 1;
        while (first <= middle && second <= end)
        {
                if (numbers[first] <= numbers[second])
                {
                        sorted.push_back(numbers[first]);
                        ++first;
                }
                else
                {
                        inverses += middle - first + 1;
                        sorted.push_back(numbers[second]);
                        ++second;
                }
        }

        while (first <= middle)
        {
                sorted.push_back(numbers[first]);
                ++first;
        }
        while (second <= end)
        {
                sorted.push_back(numbers[second]);
                ++second;
        }

        for (size_t i = start; i <= end; i++)
        {
                numbers[i] = sorted[i - start];
        }

        return inverses;
}

int main()
{
        std::vector<uint32_t> numbers;
        size_t n = 0;
        scanf("%u", &n);
        numbers.reserve(n);

        uint32_t number = 0;
        for (size_t i = 0; i < n; i++)
        {
                scanf("%u", &number);
                numbers.push_back(number);
        }
        unsigned long long result = MergeSortInverses(numbers, 0, n - 1);

        printf("%llu", result);
        printf("%c", '\n');

        return 0;
}