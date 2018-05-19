// Task: You have to find the shortest path (with lowest overall displacement) from left upper corner to bottom right corner.
// Each cell has a value, which indicates the height of the point.
// For each traveling you pay the absolute difference (displacement) between the values in the source cell and destination cell.

#include <iostream>
#include <queue>

short matrix[1000][1000];
unsigned int distance[1000][1000];
bool visited[1000][1000];
unsigned int MAX = 5000000;
unsigned int n, m;

short rowMove[] = { 0, -1, 0, 1 };
short colMove[] = { -1, 0, 1, 0 };

struct Info
{
        short row;
        short col;
        unsigned int distance;

        bool operator<(const Info &s) const
        {
                return distance > s.distance;
        }
};

bool IsValid(short row, short col)
{
        return row >= 0 && row < n && col >= 0 && col < m;
}

void Dijkstra()
{
        std::priority_queue<Info> q;
        for (short r = 0; r < n; r++)
        {
                for (short c = 0; c < m; c++)
                {
                        visited[r][c] = 0;
                        distance[r][c] = MAX;
                        q.push({ r, c, MAX });
                }
        }

        distance[0][0] = 0;
        q.push({ 0, 0, 0 });
        while (!q.empty())
        {
                Info crr = q.top(); q.pop();

                if (crr.row == n - 1 && crr.col == m - 1)
                {
                        return;
                }

                if (visited[crr.row][crr.col] == false)
                {
                        visited[crr.row][crr.col] = true;

                        for (size_t i = 0; i < 4; i++)
                        {
                                short newRow = crr.row + rowMove[i];
                                short newCol = crr.col + colMove[i];

                                if (IsValid(newRow, newCol) && !visited[newRow][newCol])
                                {
                                        unsigned int alt = distance[crr.row][crr.col] + std::abs(matrix[crr.row][crr.col] - matrix[newRow][newCol]);
                                        if (alt < distance[newRow][newCol])
                                        {
                                                distance[newRow][newCol] = alt;
                                                q.push({ newRow, newCol, alt });
                                        }
                                }
                        }
                }
        }
}

int main()
{
        std::ios::sync_with_stdio(false);
        std::cin >> n >> m;

        for (size_t row = 0; row < n; row++)
        {
                for (size_t col = 0; col < m; col++)
                {
                        std::cin >> matrix[row][col];
                }
        }

        Dijkstra();
        std::cout << distance[n - 1][m - 1] << '\n';

    return 0;
}