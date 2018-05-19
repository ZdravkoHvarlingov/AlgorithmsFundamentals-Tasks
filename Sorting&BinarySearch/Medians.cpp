// Task: Find the median of a sequence of numbers on each adding of a new number.

#include <iostream>
#include <iomanip>

inline int GetParent(int index)
{
        return index >> 1;
}

inline int GetLeftChild(int index)
{
        return index << 1;
}

inline int GetRightChild(int index)
{
        return (index << 1) | 1;
}

void SiftUp(int16_t tree[5000], int index)
{
        int parent = GetParent(index);
        if (index <= 1 || tree[parent] >= tree[index])
        {
                return;
        }

        std::swap(tree[index], tree[parent]);
        SiftUp(tree, parent);
}

void Push(int16_t element, int16_t tree[5000], size_t &size)
{
        tree[size] = element;
        ++size;
        SiftUp(tree, size - 1);
}

int32_t Peek(int16_t tree[5000], size_t &size)
{
        return tree[1];
}

void SiftDown(int16_t tree[5000], size_t &size, int index)
{
        int leftChild = GetLeftChild(index);
        int rightChild = GetRightChild(index);
        if (index >= size || leftChild >= size)
        {
                return;
        }

        int maxIndex = leftChild;
        if (rightChild < size && tree[maxIndex] < tree[rightChild])
        {
                maxIndex = rightChild;
        }

        if (tree[maxIndex] > tree[index])
        {
                std::swap(tree[maxIndex], tree[index]);
                SiftDown(tree, size, maxIndex);
        }
}

int16_t Pop(int16_t tree[5000], size_t &size)
{
        int16_t number = tree[1];
        tree[1] = tree[size - 1];
        --size;
        SiftDown(tree, size, 1);

        return number;
}

int main()
{
        int16_t minHeap[5000];
        size_t minHeapSize = 1;
        int16_t maxHeap[5000];
        size_t maxHeapSize = 1;

        std::ios::sync_with_stdio(false);

        int n;
        std::cin >> n;
        int16_t number;
        for (size_t i = 0; i < n; i++)
        {
                std::cin >> number;
                if (maxHeapSize == 1 || Peek(maxHeap, maxHeapSize) >= number)
                {
                        Push(number, maxHeap, maxHeapSize);
                }
                else
                {
                        Push(-number, minHeap, minHeapSize);
                }
                
                if (maxHeapSize - minHeapSize == 2)
                {
                        Push(-Pop(maxHeap, maxHeapSize), minHeap, minHeapSize);
                }
                else if (minHeapSize - maxHeapSize == 2)
                {
                        Push(-Pop(minHeap, minHeapSize), maxHeap, maxHeapSize);
                }

                int16_t maxTop = maxHeapSize == 1 ? 0 : Peek(maxHeap, maxHeapSize);
                int16_t minTop = minHeapSize == 1 ? 0 : -Peek(minHeap, minHeapSize);

                double numberToPrint;
                if (maxHeapSize > minHeapSize)
                {
                        numberToPrint = maxTop;
                }
                else if (maxHeapSize < minHeapSize)
                {
                        numberToPrint = minTop;
                }
                else numberToPrint = (maxTop + minTop) / ((double)2);
                std::cout << std::setprecision(1) << std::fixed << numberToPrint << " ";
        }
        std::cout << "\n";

    return 0;
}