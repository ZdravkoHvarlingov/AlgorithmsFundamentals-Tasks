// Task: Find the minimum cost to attack a specific cell from a starting one.
// There is a matrix (which is the map) and each cell (point) has a specific cost.
// The map has a coordinate system with start upper-left corner.
// The input gives you all the costs and the start and end coordinates of the attack.

#include <iostream>
#include <queue>

short matrix[1500][1500];
unsigned int distances[1500][1500];
bool visited[1500][1500];

unsigned int MAX = 3000000;

struct Node
{
        short x, y;
        unsigned int distance;

        bool operator<(const Node &other) const
        {
                return distance > other.distance;
        }
};

short n, m, startX, startY, endX, endY;

short rowMove[] = { 0, -1, 0, 1 };
short colMove[] = { -1, 0, 1, 0 };

bool IsValid(short x, short y)
{
        return x >= 0 && x < n &&
                y >= 0 && y < m;
}

void Dijkstra()
{
        for (size_t r = 0; r < n; r++)
        {
                for (size_t c = 0; c < m; c++)
                {
                        visited[r][c] = 0;
                        distances[r][c] = MAX;
                }
        }

        std::priority_queue<Node> q;
        distances[startX][startY] = matrix[startX][startY];
        q.push({ startX, startY, (unsigned int)matrix[startX][startY] });

        while (!q.empty())
        {
                Node crr = q.top(); q.pop();

                if (visited[crr.x][crr.y] == false)
                {
                        visited[crr.x][crr.y] = true;

                        if (crr.x == endX && crr.y == endY)
                        {
                                return;
                        }

                        for (size_t i = 0; i < 4; i++)
                        {
                                short newRow = crr.x + rowMove[i];
                                short newCol = crr.y + colMove[i];

                                if (IsValid(newRow, newCol) && distances[newRow][newCol] > distances[crr.x][crr.y] + matrix[newRow][newCol])
                                {
                                        distances[newRow][newCol] = distances[crr.x][crr.y] + matrix[newRow][newCol];

                                        q.push({ newRow, newCol, distances[newRow][newCol] });
                                }
                        }
                }
        }
}

int main()
{
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m;

        for (size_t r = 0; r < n; r++)
        {
                for (size_t c = 0; c < m; c++)
                {
                        std::cin >> matrix[r][c];
                }
        }

        std::cin >> startX >> startY >> endX >> endY;
        --startX; --startY; --endX; --endY;

        short temp = startY;
        startY = startX;
        startX = temp;

        temp = endY;
        endY = endX;
        endX = temp;

        Dijkstra();

        std::cout << distances[endX][endY] << '\n';

    return 0;
}