//naive design by Jiang Jiuzhang
//2015200101005@std.uestc.edu.com
//2227271J@student.gla.ac.uk
//jiu@myself.com

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int matrix[5][5];
int known[5][5];
int rows[5];
int cols[5];
int shapes[5];//depends on puzzles

//puzzle 6 for example.
shapes[0]={{0,0},{0,1},{1,0},{2,0},{3,0}};//shape A
shapes[1]={{0,2},{0,3},{0,4},{1,1},{1,2}};//shape B
shapes[2]={{4,0},{4,1},{3,1},{2,1},{2,2}};//shape C
shapes[3]={{4,2},{3,2},{3,3},{2,3},{1,3}};//shape 0
shapes[4]={{4,3},{4,4},{3,4},{2,4},{1,4}};//shape DE

//cell transform
void set_cell(int i, int j, int n)
{
    matrix[i][j] = n;
}

int clear_cell(int i, int j)
{
    int n = matrix[i][j];
    matrix[i][j] = 0;
    return n;
}

//load puzzle
void init_known(size_t count, char** cells)
{
    for (int c = 0; c < count; ++c) {
        char* cell = cells[c];
        int i, j, n;
        sscanf(cell, "%1d%1d%1d", &i, &j, &n);
        //format of puzzle should be (i,j,n)*5
        set_cell(i-1, j-1, n);
        known[i-1][j-1] = 1;
    }
}

/* Attention! these part may change 
bool check(int i, int j, int n)
{
	return ;
}
*/

bool cell(int i, int j)
{
    int n = clear_cell(i, j);
    while (++n <= 5) {
        if (check(i, j, n)) {
            set_cell(i, j, n);
            return true;
        }
    }
    return false;
}

void solve_puzzle(void)
{
    int n = 0;
    while (1) {
        while (n < 25 && known[n/5][n%5]) {
            ++n;
        }
        if (n >= 25) {
            break;
        }
        if (cell(n/5, n%5)) {
            ++n;
        } else {
            do {
                --n;
            } while (n >= 0 && known[n/5][n%5]);
            if (n < 0) {
                break;
            }
        }
    }
}

int main(int argc, char** argv)
{
    init_bits();
    init_known(argc-1, argv+1);
    solve_puzzle();
    //return EXIT_SUCCESS;
}
//check the memory and find the out put of solve_puzzle.