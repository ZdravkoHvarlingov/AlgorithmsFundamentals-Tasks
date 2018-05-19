// Task: Given the coordinates of two rot apples and specific amount of time - find the number of FINE apples after that time elapse.
// For each step all neighbour apples of a rot one become rot too.

#include <iostream>
#include <queue>

short matrix[1000][1000] = { 0 };
short rowMove[] = { -1, 0, 1, 0 };
short colMove[] = { 0, 1, 0, -1 };
short n;
short m;
short t;
short apples;
unsigned int rotApples;

bool IsInside(short row, short col)
{
        return row >= 0 && row < n &&
                col >= 0 && col < m;
}

struct Position
{
        short row;
        short col;
        short range;
};

void RotApples(short row, short col, short range, short visitedValue)
{
        std::queue<Position> q;
        q.push({ row, col, range });

        while (!q.empty())
        {
                Position crr = q.front();
                q.pop();

                if (crr.range > 0)
                {
                        for (size_t i = 0; i < 4; i++)
                        {
                                short newRow = crr.row + rowMove[i];
                                short newCol = crr.col + colMove[i];

                                if (IsInside(newRow, newCol) && matrix[newRow][newCol] != visitedValue)
                                {
                                        q.push({ newRow, newCol, crr.range - 1 });
                                        if (matrix[newRow][newCol] == 0)
                                        {
                                                ++rotApples;
                                        }
                                        matrix[newRow][newCol] = visitedValue;
                                }
                        }
                }
        }
}

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin >> n;
        std::cin >> m;
        std::cin >> t;

        apples = 0;

        short coordinates[4];

        std::cin >> coordinates[0];
        coordinates[0] = n - coordinates[0];
        std::cin >> coordinates[1];
        coordinates[1]--;
        matrix[coordinates[0]][coordinates[1]] = 1;
        ++apples;

        std::cin >> coordinates[2];
        if (!std::cin.eof())
        {
                coordinates[2] = n - coordinates[2];
                std::cin >> coordinates[3];
                coordinates[3]--;
                matrix[coordinates[2]][coordinates[3]] = 1;
                ++apples;
        }

        rotApples = apples;

        RotApples(coordinates[0], coordinates[1], t, 1);
        if (apples == 2)
        {
                RotApples(coordinates[2], coordinates[3], t, 2);
        } 

        std::cout << n * m - rotApples << "\n";

        return 0;
}