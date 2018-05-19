// We have NxM matrix with two kind of cells - dots '.' and stars '*'.
// We can pass through the dots but not through the stars because each star '*' is a wall.
// For each '*' with coordinates (x, y) we have to calculate the number of elements in the component, which includes (x, y), IF that star was a dot.
// The ouput should be a NxM matrix with stars replaced with that value mod 10.

//Example input:
// 3 3
// *.*
// .*.
// *.* 

//Example output:
// 3.3
// .5.
// 3.3

#include <iostream>
#include <set>

char board[1001][1001];
short n, m;
std::set<unsigned int> used;
bool visited[1000][1000] = { 0 };
unsigned int component[1000][1000] = { 0 };
unsigned int componentNumber[1000000] = { 0 };

unsigned int crrComponent;
unsigned int amount;

short rowMove[] = { 0, -1, 0, 1 };
short colMove[] = { -1, 0, 1, 0 };

bool IsValid(short row, short col)
{
        return row >= 0 && row < n &&
                col >= 0 && col < m;
}

void DFSVisit(short row, short col)
{
        visited[row][col] = true;
        ++amount;

        component[row][col] = crrComponent;

        for (size_t i = 0; i < 4; i++)
        {
                short newRow = row + rowMove[i];
                short newCol = col + colMove[i];

                if (IsValid(newRow, newCol) && board[newRow][newCol] == '.' && visited[newRow][newCol] == false)
                {
                        DFSVisit(newRow, newCol);
                }
        }
}

void DFS()
{
        crrComponent = 0;

        for (size_t i = 0; i < n; i++)
        {
                for (size_t j = 0; j < m; j++)
                {
                        if (board[i][j] == '.' && visited[i][j] == false)
                        {
                                amount = 0;
                                DFSVisit(i, j);
                                componentNumber[crrComponent] = amount;
                                ++crrComponent;
                        }
                }
        }
}

int main()
{
        std::ios::sync_with_stdio(false);

        std::cin >> n >> m;
        std::cin.tie(NULL);
        std::cin.get();
        for (size_t i = 0; i < n; i++)
        {
                std::cin.getline(board[i], m + 1);
        }

        DFS();

        unsigned int result;
        short newRow, newCol;
        for (size_t i = 0; i < n; i++)
        {
                for (size_t j = 0; j < m; j++)
                {
                        if (board[i][j] == '*')
                        {
                                used.clear();
                                result = 1;
                                for (size_t k = 0; k < 4; k++)
                                {
                                        newRow = i + rowMove[k];
                                        newCol = j + colMove[k];

                                        if (IsValid(newRow, newCol) && board[newRow][newCol] == '.' && used.count(component[newRow][newCol]) == 0)
                                        {
                                                used.insert(component[newRow][newCol]);
                                                result += componentNumber[component[newRow][newCol]];
                                        }
                                }
                                result %= 10;

                                board[i][j] = '0' + result;
                        }
                }

                board[i][m] = '\0';
        }

        for (size_t i = 0; i < n; i++)
        {
                std::cout << board[i] << '\n';
        }

    return 0;
}