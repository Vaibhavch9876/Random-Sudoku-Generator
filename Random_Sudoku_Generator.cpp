
/*************************************************************************************************/
/***************************** RANDOM SUDOKU GENERATOR *******************************************/
/*************************************************************************************************/
/****************************** BY : VAIBHAV CHOUDHARY *******************************************/
/*************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
#define N 9

// SUDOKU GRID 9 * 9
int grid[N][N];

// FUNCTION DECLARATION
void initialize();
bool randomSudoku();
unordered_set<int> generate_set();
bool get_RC(int &row, int &col);
bool isSafe(int i, int j, int num);
bool isSafe_Box(int row, int col, int num);
bool isSafe_RC(int row, int col, int num);
void Special_print(int grid[N][N]);
int count_Solution(int & ans);
void make_empty();
void make_more_empty();

// MAIN DRIVER FUNCTION
int main()
{
    initialize();
    randomSudoku();
    make_empty();
    make_more_empty();
    Special_print(grid);
    system("pause");
    return 0;
}
// END OF MAIN

// RANDOM SUDOKU GENERATOR
bool randomSudoku()
{
    unordered_set<int> random_number = generate_set();
    int i, j;
    if(get_RC(i, j))
    {
        for (int num : random_number)
        {
            if (isSafe(i, j, num))
            {
                grid[i][j] = num;
                if (randomSudoku())
                    return true;
                else
                    grid[i][j] = 0;
            }
        }
    }
    else
        return true;
    return false;
}

// GENERATE RANDOM SET OF 9 VALUES
unordered_set<int> generate_set()
{
    srand(time(0));
    unordered_set<int> s;
    while(s.size() != 9)
    {
        int n = rand() % 9 + 1;
        s.insert(n);
    }
    return s;
}

// RETURNS EMPTY CELL AND ITS ROW AND COLUMN VALUE IF FOUND
bool get_RC(int &row, int &col)
{
    for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
        if (grid[row][col] == 0)
            return true;
    return false;
}

// MAKING EMPTY GRID
void initialize()
{
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
        grid[i][j] = 0;
}

// CHECK FOR REDUNDANCY
bool isSafe(int i, int j, int num)
{
    return isSafe_RC(i, j, num) && isSafe_Box(i, j, num);
}

// CHECKS ROW AND COLUMNS FOR REDUNDANCY
bool isSafe_RC(int row, int col, int num)
{
    for (int i = 0; i < N; i++)
    {
        if (grid[row][i] == num)
                return false;
        if (grid[i][col] == num)
                return false;
    }
    return true;
}

// CHECKS 3 * 3 BOXES FOR REDUNDANCY
bool isSafe_Box(int row, int col, int num)
{
    int boxx = row / 3;
    int boxy = col / 3;

    for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
    {
        if (grid[boxx * 3 + i][boxy * 3 + j] == num)
            return false;
    }
    return true;
}

// FOR PRINTING GRID
void Special_print(int grid[N][N])
{
    int j;
    cout << "\n\n";
    for (int i = 0; i < N; i++) {
        cout << "\t\t\t\t\t||";
        if ((i) % 3)
            cout << "-------------------------------------||\n\t\t\t\t\t||";
        else
            cout << "=====================================||\n\t\t\t\t\t||";
        for (int j = 0; j < N; j++)
        {
            if (j % 3 == 0)
                cout << "\b| ";
            cout << grid[i][j] << " | ";
        }
        cout << "\b|\n";
    }
    cout << "\t\t\t\t\t||=====================================||";
}

// RETURNS NUMBER OF SOLUTIONS
int count_Solution(int & ans)
{
    int i, j;

    if (get_RC(i, j))
    {
        for (int num = 1; num <= N; num++)
        {
            if (isSafe(i, j, num))
            {
                grid[i][j] = num;
                int prev = ans;
                ans = count_Solution(ans);
                    grid[i][j] = 0;
            }
        }
    }
    else
        ans++;
    return ans;
}

// CLEARS CELLS
void make_empty()
{
    srand(time(0));
    int i = 0, j = 0;
    while(grid[i][j] == 0)
    {
        i = rand() % 9;
        j = rand() % 9;
    }
    int val = grid[i][j];
    grid[i][j] = 0;
    int a = 0;
    if (count_Solution(a) == 1)
        make_empty();
    else
        grid[i][j] = val;
}

// CLEARS MORE CELLS
void make_more_empty()
{
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
        int a = 0;
        int val = grid[i][j];
        grid[i][j] = 0;
        if(count_Solution(a) == 1)
            continue;
        else
            grid[i][j] = val;
    }
}
