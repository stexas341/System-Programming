#include <stdio.h>

#define tonos 39
#define dialytika 34

int n(int c, int dif[]);
int m(int c, int dif[]);
int g(int c, int dif[]);
int two_out(int c, char dif1to2[][2]);
int any(int c, char letters[][3], int greek[]);


int main(void){
    char letters[50][3];
    int dif[6]; /* dyo se 1*/
    char dif1to2[4][2]; /* 1 se 2*/
    int greek[48];
    int i=0;
    int j=193;
    int c;

    letters[0][0] = 'A'; letters[0][1] = tonos;
    letters[1][0] = 'V';
    letters[2][0] = 'G';
    letters[3][0] = 'D';
    letters[4][0] = 'E'; letters[4][1] = tonos;
    letters[5][0] = 'Z';
    letters[6][0] = 'H'; letters[6][1] = tonos;
    letters[7][0] = '8';
    letters[8][0] = 'I'; letters[8][1] = tonos; letters[8][2] = dialytika;
    letters[9][0] = 'K';
    letters[10][0] = 'L';
    letters[11][0] = 'M';
    letters[12][0] = 'N';
    letters[14][0] = 'O'; letters[14][1] = tonos;
    letters[15][0] = 'P';
    letters[16][0] = 'R';
    letters[17][0] = 'S';
    letters[18][0] = 'T';
    letters[19][0] = 'Y'; letters[19][1] = tonos; letters[19][2] = dialytika;
    letters[20][0] = 'F';
    letters[21][0] = 'X';
    letters[23][0] = 'W'; letters[23][1] = tonos;

    /*Lowercase*/
    letters[24][0] = 'a'; letters[24][1] = tonos;
    letters[25][0] = 'v';
    letters[26][0] = 'g';
    letters[27][0] = 'd';
    letters[28][0] = 'e'; letters[28][1] = tonos;;
    letters[29] [0]= 'z';
    letters[30] [0]= 'h'; letters[30][1] = tonos;
    letters[31] [0]= '8';
    letters[32] [0]= 'i'; letters[32][1] = tonos; letters[32][2] = dialytika;
    letters[33] [0]= 'k';
    letters[34][0] = 'l';
    letters[35][0] = 'm';
    letters[36][0] = 'n';
    letters[38] [0]= 'o'; letters[38][1] = tonos;
    letters[39] [0]= 'p';
    letters[40] [0]= 'r';
    letters[41] [0]= 's';
    letters[42] [0]= 't';
    letters[43] [0]= 'y'; letters[43][1] = tonos; letters[43][2] = dialytika;
    letters[44] [0]= 'f';
    letters[45] [0]= 'x';
    letters[47] [0]= 'w'; letters[47][1] = tonos;

    dif[0] = 'd';
    dif[1] = 'b';
    dif[2] = 'g';
    dif[3] = 'B';
    dif[4] = 'D';
    dif[5] = 'G';

    dif1to2[0][0] = 'P';
    dif1to2[0][1] = 'S';
    dif1to2[1][0] = 'K';
    dif1to2[1][1] = 'S';

    dif1to2[2][0] = 'p';
    dif1to2[2][1] = 's';
    dif1to2[3][0] = 'k';
    dif1to2[3][1] = 's';
    
    for(i = 0; i < 48; i++) {
        if(j == 210) {
            j++;
        }

        if(j == 218) {
            j = 225;
        }

        if(j == 242) {
            j = 243;
        }
        greek[i] = j;
        j++;
    }

    while((c = getchar()) != EOF)
    {
        switch(c)
        {
            case 237: n(c, dif);                
            break;
            case 205: n(c, dif);                
            break;
            case 236: m(c, dif);
            break;
            case 204: m(c, dif);
            break;
            case 227: g(c, dif);
            break;
            case 195: g(c, dif);
            break;
            case 206: two_out(c, dif1to2);
            break;
            case 216: two_out(c, dif1to2);
            break;
            case 238: two_out(c, dif1to2);
            break;
            case 248: two_out(c, dif1to2);
            break;
            default: any(c, letters, greek);
            break;
        }
    }
    printf("\n");
    return 0;
}

int any(int c, char letters[][3], int greek[]) {
    int k;
    for(k = 0; k < 48; k++) {
        if(greek[k] == c) {
            c = letters[k][0];
            break;
        }
    }
    printf("%c", c);
    return 0;
}

int n(int c, int dif[]) {
    
    if(c == 212 || c == 244) {
        c = dif[0];
    }
    if(c == 244) {
        c = dif[4];
    }
    printf("%c", c);
    return 0;
}

int m(int c, int dif[]) {
    int ch;
    ch = getchar();
    if(ch == 208 || ch == 240) {
        if(c == 204) {
            c = dif[3];
        }else{
            c = dif[1];
        }
    }
    printf("%c", c);
    return 0;
}

int g(int c, int dif[]) {
    c = getchar();
    if(c == 202 || c == 234) {
        c = dif[2];
    }
    if(c == 234) {
        c = dif[5];
    }
    printf("%c", c);
    return 0;
}

int two_out(int c, char dif1to2[][2]) {
    char ch[2];

    if(c == 206) {
        ch[0] = dif1to2[0][0];
        ch[1] = dif1to2[0][1];
    }
    if(c == 216) {
        ch[0] = dif1to2[1][0];
        ch[1] = dif1to2[1][1];
    }

    if(c == 238) {
        ch[0] = dif1to2[2][0];
        ch[1] = dif1to2[2][1];
    }
    if(c == 248) {
        ch[0] = dif1to2[3][0];
        ch[1] = dif1to2[3][1];
    }
    printf("%c%c", ch[0], ch[1]);
    return 0;
}