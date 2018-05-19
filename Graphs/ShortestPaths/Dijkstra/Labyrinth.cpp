// There is a labyrinth with N rowns and M columns. if the cell has value # - the cell is a wall, if the value is . - the cell is not wall.
// Task: Find the minimum number of steps in order to exit the labyrinth with given input entrance and exit.
// More direct approach can be used - BFS

#include <vector>
#include <iostream>
#include <bitset>
#include <queue>

unsigned int distances[1005][1005];
std::bitset<1000025> visited;
bool matrix[1005][1005];
unsigned int MAX = 100000000;
unsigned int n, m;
int rowMove[] = { -1, 0, 1, 0 };
int colMove[] = { 0, 1, 0, -1 };


struct Pair
{
        unsigned int row;
        unsigned int col;
        unsigned int distance;
};

struct Comparator
{
        bool operator()(const Pair &first, const Pair &second) const
        {
                if (first.distance == second.distance)
                {
                        return first.row * first.col > second.row * second.col;
                }
                return first.distance > second.distance;
        }
};

bool IsAvailable(int row, int col)
{
        return row >= 0 && row < n &&
                col >= 0 && col < m &&
                matrix[row][col] == 1;
}

int DijkstraShortestPath(unsigned int startRow, unsigned int startCol, unsigned int finishRow, unsigned int finishCol)
{
        if (matrix[finishRow][finishCol] == 0)
        {
                return -1;
        }

        visited.flip();
        std::priority_queue<Pair, std::vector<Pair>, Comparator> q;

        for (size_t i = 0; i < n; i++)
        {
                for (size_t j = 0; j < m; j++)
                {
                        if (matrix[i][j])
                        {
                                distances[i][j] = MAX;
                                q.push({ i, j, MAX });
                                visited.set(i * m + j, false);
                        }
                }
        }

        distances[startRow][startCol] = 0;
        q.push({ startRow, startCol, 0 });

        while (!visited.all())
        {
                Pair node = q.top(); q.pop();
                if (!visited.test(node.row * m + node.col));
                {
                        visited.set(node.row * m + node.col);

                        if (distances[node.row][node.col] == MAX || (node.row == finishRow && node.col == finishCol))
                        {
                                return distances[finishRow][finishCol] == MAX ? -1 : distances[finishRow][finishCol];
                        }

                        for (size_t i = 0; i < 4; i++)
                        {
                                int newRow = node.row + rowMove[i];
                                int newCol = node.col + colMove[i];

                                unsigned int alt = distances[node.row][node.col] + 1;
                                if (IsAvailable(newRow, newCol) && alt < distances[newRow][newCol])
                                {
                                        distances[newRow][newCol] = alt;
                                        q.push({ (unsigned int)newRow, (unsigned int)newCol, alt });
                                }
                        }
                }
        }

        return distances[finishRow][finishCol];
}

int main()
{
        std::cin >> n >> m;

        for (size_t i = 0; i < 1005; i++)
        {
                for (size_t j = 0; j < 1005; j++)
                {
                        matrix[i][j] = 0;
                }
        }

        char crr;
        for (size_t i = 0; i < n; i++)
        {
                for (size_t j = 0; j < m; j++)
                {
                        std::cin >> crr;

                        if (crr == '.')
                        {
                                matrix[i][j] = 1;
                        }
                }
        }
        unsigned int startRow, startCol, finishRow, finishCol;
        std::cin >> startRow >> startCol >> finishRow >> finishCol;

        std::cout << DijkstraShortestPath(startRow, startCol, finishRow, finishCol) << "\n";

        return 0;
}