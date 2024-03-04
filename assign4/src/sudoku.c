#include "sudoku.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>

Grid_T sudoku_read(void)
{
    Grid_T sudoku;
    int Cell_Num[9][9];

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (scanf("%d", &Cell_Num[i][j]) != 1) {
                fprintf(stderr, "Error: Could not read input.\n");
                exit(EXIT_FAILURE);
            }
            if(Cell_Num[i][j]>9 || Cell_Num[i][j]<0){
                fprintf(stderr, "Error: Invalid input value %d.\n", Cell_Num[i][j]);
                exit(EXIT_FAILURE);
            }
        }
        getchar(); 
    }

    sudoku = grid_init(sudoku, Cell_Num);
    return sudoku;
}

void sudoku_print(FILE *s, Grid_T g){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fprintf(s, "%d ", g.cell[i][j].choices[0]); 
        }
        fprintf(s, "\n");
    }
}

int sudoku_is_correct(Grid_T g){
    int i, j, k, num;
    int row_start, col_start;
    int count[10] = {0}; 

    
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            num = g.cell[i][j].choices[0];
            if (num < 1 || num > 9) {
                return 0;
            }
        }
    }

    for (i = 0; i < 9; i++) {
        for (k = 0; k < 9+1; k++) {
            count[k] = 0; 
        }
        for (j = 0; j < 9; j++) {
            num = g.cell[i][j].choices[0];
            count[num]++;
            if (count[num] > 1) {
                return 0;
            }
        }
    }

   
    for (j = 0; j < 9; j++) {
        for (k = 0; k < 9+1; k++) {
            count[k] = 0; 
        }
        for (i = 0; i < 9; i++) {
            num = g.cell[i][j].choices[0];
            count[num]++;
            if (count[num] > 1) {
                return 0;
            }
        }
    }

  
    for (row_start = 0; row_start < 9; row_start += 3) {
        for (col_start = 0; col_start < 9; col_start += 3) {
            for (k = 0; k < 9+1; k++) {
                count[k] = 0;
            }
            for (i = row_start; i < row_start+3; i++) {
                for (j = col_start; j < col_start+3; j++) {
                    num = g.cell[i][j].choices[0];
                    count[num]++;
                    if (count[num] > 1) {
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}

Grid_T sudoku_solve(Grid_T g, Choice_T c){
    int i, j, k, count=0;
    for(i=0 ; i<9 ; i++){
        for(j=0 ; j<9 ; j++){
            if(g.cell[i][j].choices[0]==0){
                count++;
            }
        }
    }
    if(count==0){
        if(sudoku_is_correct(g)){
            return g;
        } else {
            g.unique=0;
            return g;
        }
    }

    /*checking case where every cell has only 1 option */
    int progress = 0;
    do {
        progress = 0;
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                if (g.cell[i][j].count == 1 && g.cell[i][j].choices[0] == 0) {
                    for (k = 1; k < 9 + 1; k++) {
                        if (g.cell[i][j].choices[k] == 1) {
                            g.cell[i][j].choices[0] = k;
                            c.i = i; c.j = j; c.n = k;
                            g = grid_update(g, c);
                            progress = 1;
                        }
                    }
                }
            }
        }
    } while (progress);

    /*checking all possible values for an empty cell*/
    int min_count = 10;
    int best_i = -1, best_j = -1;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (g.cell[i][j].choices[0] == 0 && g.cell[i][j].count < min_count) {
                min_count = g.cell[i][j].count;
                best_i = i; best_j = j;
            }
        }
    }

    /*recursively try different choices for the empty cell*/
    for (k = 1; k < 9 + 1; k++) {
        if (g.cell[best_i][best_j].choices[k] == 1) {
            Grid_T new_grid = grid_copy(g);
            new_grid.cell[best_i][best_j].choices[0] = k;
            c.i = best_i; c.j = best_j; c.n = k;
            new_grid = grid_update(new_grid, c);
            new_grid = sudoku_solve(new_grid, c);
            if (new_grid.unique) {
                return new_grid;
            }
        }
    }

    g.unique = 0;
    return g;
}

Grid_T grid_copy(Grid_T g) {
    Grid_T copy;
    int i, j, k;

    /* Copy the values in each cell of the grid */
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            for (k = 0; k < 9+1; k++) {
                copy.cell[i][j].choices[k] = g.cell[i][j].choices[k];
            }
            copy.cell[i][j].count = g.cell[i][j].count;
        }
    }

    copy.unique = g.unique;

    return copy;
}

int main(int argc, char **argv) {
    Grid_T g;
    Choice_T c;
    int flag;
    
    c.i=0; c.j=0; c.n=0;
  
    if(argc==1){
        FILE *outfile = stderr;
        g = sudoku_read();

        sudoku_print(outfile, g);
        fprintf(outfile, "\n");

        g=sudoku_solve(g,c);
        
        if(g.unique==1){
            fprintf(outfile, "Sudoku has unique solution\n");
        }

        sudoku_print(outfile, g);
        fprintf(outfile, "\n");
        fclose(outfile);
        
    } else if(argc==2){
        FILE *outfile = stderr;
        g = sudoku_read();

        sudoku_print(outfile, g);
        fprintf(outfile, "\n");

        flag = sudoku_is_correct(g);
        if(flag==1){
            fprintf(outfile, "Sudoku is correct\n");
        } else { fprintf(outfile, "Sudoku is not correct\n"); }
        fclose(outfile);

    } else if(argc==3 || argc==4 ){
        FILE *outfile = stdout;
        fprintf(outfile, "Not implemented\n");
        fclose(outfile);
    }

    
    return 0;
}
