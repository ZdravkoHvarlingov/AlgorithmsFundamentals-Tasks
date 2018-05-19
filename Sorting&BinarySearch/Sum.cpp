// Task: There are N numbers and M sums. For each sum find if there are two numbers A and B such that A + B = sum;

#include <iostream>

int numbers[1000000];
int n, m;

int HoarePartition(int start, int end)
{
        std::swap(numbers[start], numbers[(start + end) / 2]);

        unsigned int pivot = numbers[start];
        int i = start - 1;
        int j = end + 1;

        while (true)
        {
                do
                {
                        --j;
                } while (numbers[j] > pivot);
                do
                {
                        ++i;
                } while (numbers[i] < pivot);

                if (i >= j)
                {
                        return j;
                }

                std::swap(numbers[i], numbers[j]);
        }

        return j;
}

void InsertionSort(int start, int end)
{
        for (size_t i = start + 1; i <= end; i++)
        {
                unsigned int crr = numbers[i];
                int j = i - 1;

                while (j >= 0 && numbers[j] > crr)
                {
                        numbers[j + 1] = numbers[j];

                        --j;
                }

                numbers[j + 1] = crr;
        }
}

void QuickSort(int start, int end)
{
        if (end - start < 10)
        {
                InsertionSort(start, end);

                return;
        }

        int partition = HoarePartition(start, end);
        QuickSort(start, partition);
        QuickSort(partition + 1, end);
}

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin >> n >> m;
        for (size_t i = 0; i < n; i++)
        {
                std::cin >> numbers[i];
        }

        QuickSort(0, n - 1);

        for (size_t i = 0; i < m; i++)
        {
                int sum;
                std::cin >> sum;

                int left = 0;
                int right = n - 1;
                bool found = false;
                while (left < right && !found)
                {
                        if (numbers[left] + numbers[right] == sum)
                        {
                                found = true;
                        }
                        else if (numbers[left] + numbers[right] > sum)
                        {
                                --right;
                        }
                        else
                        {
                                ++left;
                        }
                }

                found ? std::cout << "YES\n" : std::cout << "NO\n";
        }

    return 0;
}