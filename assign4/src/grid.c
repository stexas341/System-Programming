#include "grid.h"
#include<stdlib.h>
#include<stdio.h>


Grid_T grid_update(Grid_T g, Choice_T c){
    g.cell[c.i][c.j].choices[0] = c.n;
    g.cell[c.i][c.j].choices[c.n] = 0;

    int a, b;

    if(c.n != 0){
        for(a = 0; a < 9; a++){
            if(g.cell[c.i][a].choices[c.n] != 0){  
                g.cell[c.i][a].choices[c.n] = 0;
                g.cell[c.i][a].count--;
            }
        }
        for(b = 0; b < 9; b++){
            if(g.cell[b][c.j].choices[c.n] != 0){
                g.cell[b][c.j].choices[c.n] = 0;
                g.cell[b][c.j].count--;
            }
        }

        int block_row = c.i / 3;
        int block_col = c.j / 3;

        for(a = block_row * 3; a < block_row * 3 + 3; a++){
            for(b = block_col * 3; b < block_col * 3 + 3; b++){
                if(g.cell[a][b].choices[c.n] != 0){
                    g.cell[a][b].choices[c.n] = 0;
                    g.cell[a][b].count--;
                }
            }
        }
    }   

    return g;
}

Grid_T grid_init(Grid_T g, int v[9][9]){
    int i, j, b;

    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            g.cell[i][j].choices[0] = v[i][j];

            if(g.cell[i][j].choices[0] == 0){
                for(b = 1; b < 10; b++){
                   g.cell[i][j].choices[b] = 1;
                }
                g.cell[i][j].count = 9;
            }
            
            else { 
                for(b = 1; b < 10; b++){
                    g.cell[i][j].choices[b] = 0; 
                }
                g.cell[i][j].count = 1;
            }
        }
    }

    return g;
}
Choice_T grid_iterate(Grid_T g, Choice_T t) {
    Choice_T k = {0, 0, 0}; 
    int row = t.i;
    int col = t.j;
    int next_choice = t.n + 1;

    for(; next_choice < 10; next_choice++) {
        if(g.cell[row][col].choices[next_choice] == 1) {
            k.n = next_choice;
            k.i = row;
            k.j = col;
            return k;
        }
    }

    return k;
}


Choice_T grid_exist_unique(Grid_T g){
    int i, j, k;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(g.cell[i][j].choices[0] == 0){
                int cnt = 0;
                int value = 0;
                for(k = 1; k < 10; k++){
                    if(g.cell[i][j].choices[k] == 1){
                        cnt++;
                        value = k;
                    }
                }
                if(cnt == 1){
                    Choice_T c;
                    c.i = i;
                    c.j = j;
                    c.n = value;
                    return c;
                }
            }
        }
    }
    Choice_T c;
    c.i = 0;
    c.j = 0;
    c.n = 0;
    return c;
}

Choice_T grid_read_value(Grid_T g, Choice_T c){
    c.n = g.cell[c.i][c.j].choices[0];
    return c;
}

void grid_cell_print(FILE *stream, Grid_T g, Choice_T c){
    fprintf(stream, "%d %d", g.cell[c.i][c.j].choices[0], g.cell[c.i][c.j].count);
}

int grid_unique(Grid_T g){
    return g.unique;
}
Grid_T grid_clear_unique(Grid_T g){
    g.unique=0;
    return g;
}


