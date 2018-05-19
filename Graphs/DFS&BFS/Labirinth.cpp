#include <iostream>

bool graph[1000][1000];
int rowMove[] = { -1, 0, 1, 0 };
int colMove[] = { 0, 1, 0, -1 };
unsigned int n;
unsigned int m;
unsigned int maxLength;
unsigned int maxRow;
unsigned int maxCol;

bool IsInside(int row, int col)
{
        return row >= 0 && row < n &&
                col >= 0 && col < m;
}

void MakeDFS(unsigned int crrRow, unsigned int crrCol, unsigned int crrLength)
{
        if (crrLength > maxLength)
        {
                maxLength = crrLength;
                maxRow = crrRow;
                maxCol = crrCol;
        }

        for (size_t i = 0; i < 4; i++)
        {
                int newRow = crrRow + rowMove[i];
                int newCol = crrCol + colMove[i];

                if (IsInside(newRow, newCol) && graph[newRow][newCol] == 1)
                {
                        graph[newRow][newCol] = 0;
                        MakeDFS(newRow, newCol, crrLength + 1);
                        graph[newRow][newCol] = 1;
                }
        }
}

void FindLongest()
{
        unsigned int startRow;
        unsigned int startCol;
        bool found = false;
        for (size_t i = 0; i < n && !found; i++)
        {
                for (size_t j = 0; j < m && !found; j++)
                {
                        if (graph[i][j] == 1)
                        {
                                startRow = i;
                                startCol = j;
                                found = true;
                        }
                }
        }

        graph[startRow][startCol] = 0;
        maxLength = 0;
        maxRow = startRow;
        maxCol = startCol;
        MakeDFS(startRow, startCol, 0);
        graph[startRow][startCol] = 1;

        graph[maxRow][maxCol] = 0;
        MakeDFS(maxRow, maxCol, 0);
}

int main()
{
        std::cin >> m;
        std::cin >> n;
        char c;
        for (size_t i = 0; i < n; i++)
        {
                for (size_t j = 0; j < m; j++)
                {
                        std::cin >> c;
                        graph[i][j] = c == '#' ? 0 : 1;
                }
        }

        FindLongest();
        std::cout << maxLength << "\n";

        return 0;
}