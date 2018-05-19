// Task: We have N places and M chickens and we want to place every chicken in a specific place.
// All the places are ordered in a line. The problem is that if two chickens are very close to each other they start fighting.
// We want to maximize the minimum distance between two chickens.
// The solution below gives a number K such that every two chickens are at least K places away from each other.

#include <iostream>

unsigned int places[100000];
unsigned int n, m;

int HoarePartition(int start, int end)
{
        unsigned int pivot = places[start];
        int i = start - 1;
        int j = end + 1;

        while (true)
        {
                do
                {
                        --j;
                } while (places[j] > pivot);
                do
                {
                        ++i;
                } while (places[i] < pivot);

                if (i >= j)
                {
                        return j;
                }

                std::swap(places[i], places[j]);
        }

        return j;
}

void InsertionSort(int start, int end)
{
        for (size_t i = start + 1; i <= end; i++)
        {
                unsigned int crr = places[i];
                int j = i - 1;

                while (j >= 0 && places[j] > crr)
                {
                        places[j + 1] = places[j];

                        --j;
                }

                places[j + 1] = crr;
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

bool IsSolution(int min)
{
        int crrInd = 0;
        int placed = 1;
        while (placed < m && crrInd < n)
        {
                int next = places[crrInd] + min;
                int start = crrInd;
                int end = n - 1;
                
                int result = -1;
                while (start <= end)
                {
                        int middle = (start + end) / 2;
                        if (next == places[middle])
                        {
                                result = middle;
                                break;
                        }
                        else if (places[middle] > next)
                        {
                                result = middle;
                                end = middle - 1;
                        }
                        else
                        {
                                start = middle + 1;
                        }
                }

                if (result == -1)
                {
                        return false;
                }

                crrInd = result;
                ++placed;
        }

        return placed == m;
}

int BinarySearch()
{
        int start = 1;
        int end = places[n - 1] - places[0];

        int result = -1;
        while (start <= end)
        {
                int middle = (start + end) / 2;

                if (IsSolution(middle))
                {
                        result = middle;
                        start = middle + 1;
                }
                else
                {
                        end = middle - 1;
                }
        }

        return result;
}

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin >> n >> m;
        for (size_t i = 0; i < n; i++)
        {
                std::cin >> places[i];
        }

        QuickSort(0, n - 1);

        int finalResult = BinarySearch();
        std::cout << finalResult << "\n";

    return 0;
}