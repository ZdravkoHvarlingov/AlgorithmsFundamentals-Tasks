// Using heap in order to handle non fixed amount of numbers with specific operations:
// 	- Extracting the maximum;
//	- Adding a new number;
//	- Printing the maximum number;

#include <iostream>

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

void SiftUp(uint32_t tree[100000], int index)
{
        int parent = GetParent(index);
        if (index <= 1 || tree[parent] >= tree[index])
        {
                return;
        }

        std::swap(tree[index], tree[parent]);
        SiftUp(tree, parent);
}

void Push(uint32_t element, uint32_t tree[100000], size_t &size)
{
        tree[size] = element;
        ++size;
        SiftUp(tree, size - 1);
}

uint32_t Peek(uint32_t tree[100000], size_t &size, bool &hasNumber)
{
        if (size <= 1)
        {
                hasNumber = false;
                return -1;
        }

        hasNumber = true;
        return tree[1];
}

void SiftDown(uint32_t tree[100000], size_t &size, int index)
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

uint32_t Pop(uint32_t tree[100000], size_t &size, bool &hasNumber)
{
        if (size <= 1)
        {
                hasNumber = false;
                return -1;
        }

        uint32_t number = tree[1];
        tree[1] = tree[size - 1];
        --size;
        SiftDown(tree, size, 1);

        hasNumber = true;
        return number;
}

int main()
{
        uint32_t tree[100000];
        size_t size = 1;

        char command = 'Q';
        scanf("%c", &command);
        bool stop = false;
        bool hasNumber = false;
        while (!stop)
        {
                switch (command)
                {
                case 'A':
                {
                        uint32_t number;
                        scanf("%d", &number);
                        Push(number, tree, size);
                }
                break;
                case 'R':
                {
                        hasNumber = false;
                        uint32_t top = Pop(tree, size, hasNumber);
                        hasNumber ? printf("%u", top) : printf("%s", "Not available");
                        printf("%c", '\n');
                }
                break;
                case 'L':
                {
                        hasNumber = false;
                        uint32_t top = Peek(tree, size, hasNumber);
                        hasNumber ? printf("%u", top) : printf("%s", "Not available");
                        printf("%c", '\n');
                }
                break;
                case 'Q':
                {
                        stop = true;
                }
                break;
                default:
                        break;
                }

                if (!stop)
                {
                        scanf("%c", &command);
                }
        }

        return 0;
}