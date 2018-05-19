// QuickSort with Lomuto partition

#include <iostream>

int GetPartitionIndex(int start, int end, int numbers[100000])
{
        int pivot = numbers[end];
        int partIndex = start;
        int ind = start;
        while (ind < end)
        {
                if (numbers[ind] < pivot)
                {
                        std::swap(numbers[ind], numbers[partIndex]);
                        ++partIndex;
                }

                ++ind;
        }
        std::swap(numbers[partIndex], numbers[end]);

        return partIndex;
}

void QuickSort(int start, int end, int numbers[100000])
{
        if (start >= end)
        {
                return;
        }

        int partitionIndex = GetPartitionIndex(start, end, numbers);
        QuickSort(start, partitionIndex - 1, numbers);
        QuickSort(partitionIndex + 1, end, numbers);
}

int main()
{
        int numbers[100000];
        int n;
        std::cin >> n;

        for (size_t i = 0; i < n; i++)
        {
                std::cin >> numbers[i];
        }

        QuickSort(0, n - 1, numbers);
        
        for (size_t i = 0; i < n; i++)
        {
                std::cout << numbers[i] << " ";
        }
        std::cout << "\n";

    return 0;
}