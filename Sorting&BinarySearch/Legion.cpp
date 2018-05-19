// Task: There are N unique numbers. For each input number afterwards find the number of elements in the sequence that are less than that number.
// QuickSort with HoarePartition used + Binary search.

#include <iostream>

int c[800000];
unsigned int n;

int HoarePartition(int start, int end)
{
        int pivot = c[start];
        int i = start - 1;
        int j = end + 1;

        while (true)
        {
                do
                {
                        ++i;
                } while (c[i] < pivot);

                do
                {
                        --j;
                } while (c[j] > pivot);

                if (i >= j)
                {
                        return j;
                }

                std::swap(c[i], c[j]);
        }

        return j;
}

void QuickSort(int start, int end)
{
        if (end - start  < 15)
        {
                for (size_t i = start + 1; i <= end; i++)
                {
                        int crr = c[i];
                        int j = i - 1;
                        while (j >= start && c[j] > crr)
                        {
                                c[j + 1] = c[j];

                                --j;
                        }

                        c[j + 1] = crr;
                }

                return;
        }

        int partIndex = HoarePartition(start, end);
        QuickSort(start, partIndex);
        QuickSort(partIndex + 1, end);
}

int main()
{
        //std::ios::sync_with_stdio(false);
        //std::cin >> n;

        scanf("%d", &n);

        for (size_t i = 0; i < n; i++)
        {
                //std::cin >> c[i];
                scanf("%d", &c[i]);
        }

        QuickSort(0, n - 1);

        int number, start, end, result;
        result = 0;
        scanf("%d", &number);
        while (number != 0)
        {
                if (result == -1)
                {
                        result = 0;
                }
                if (c[result] > number)
                {
                        start = result - (c[result] - number);
                        end = result;
                }
                else
                {
                        start = result;
                        end = result + (number - c[result]);
                }

                start = start < 0 ? 0 : start;
                end = end > n - 1 ? n - 1 : end;

                result = -1;
                while (start <= end)
                {
                        int middle = (start + end) / 2;
                        if (c[middle] == number)
                        {
                                result = middle;
                                break;
                        }
                        else if (c[middle] < number)
                        {
                                start = middle + 1;
                        }
                        else
                        {
                                end = middle - 1;
                        }
                }
                printf("%d\n", result);

                scanf("%d", &number);
        }

        return 0;
}