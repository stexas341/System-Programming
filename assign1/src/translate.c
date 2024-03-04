/* SFAKIANAKIS STYLIANOS csd4513*/
#include <stdio.h>

#define tonos 39
#define dialytika 34

enum fsm{any, mkef, nkef, mmikr, nmikr}state; /*dhlwsh katastasewn fsm*/

void pinakas(char grammata[256][3])
{
    int i = 0,j = 0;

	char mikra[25] = {'a','v','g','d','e','z','h','8','i','k','l','m','n','j','o','p','r','s','s','t','y','f','x','y','w'}; /* 2o s gia to s teliko*/
	char kefalaia[25] = {'A','V','G','D','E','Z','H','8','I','K','L','M','N','J','O','P','R','S','S','T','Y','F','X','Y','W'};

   	for(i = 0; i < 256; i++){ /*arxikopoihsh*/
		grammata[i][0] = i;
		grammata[i][1] = '\0';
		grammata[i][2] = '\0';
	}

	for(i = 225; i < 251; i++){  /*mikra*/
		grammata[i][0] = mikra[j];
		j++;
	}
    j=0;  /*kefalaia*/
	for(i = 193; i <218; i++){
		grammata[i][0] = kefalaia[j];
		j++;
	}

	/*mikra me tono*/
	grammata[220][0] = 'a';
	grammata[220][1] = tonos;
	grammata[221][0] = 'e';
	grammata[221][1] = tonos;
	grammata[222][0]  = 'h';
	grammata[222][1] = tonos;
	grammata[223][0] = 'i';
	grammata[223][1] = tonos;
	grammata[252][0] = 'o';
	grammata[252][1] = tonos;
	grammata[253][0] = 'y';
	grammata[253][1] = tonos;
	grammata[254][0] = 'w';
	grammata[254][1] = tonos;
	/*kefalaia me tono*/
	grammata[182][0] = 'A';
    grammata[182][1] = tonos;
	grammata[184][0] = 'E';
	grammata[184][1] = tonos;
	grammata[185][0] = 'H';
	grammata[185][1] = tonos;
	grammata[186][0] = 'I';
	grammata[186][1] = tonos;
	grammata[188][0] = 'O';
	grammata[188][1] = tonos;
	grammata[190][0] = 'Y';
	grammata[190][1] = tonos;
	grammata[191][0] = 'W';
	grammata[191][1] = tonos;
	/*dialitika*/
	grammata[218][0] = 'I';
	grammata[218][1] = dialytika;
	grammata[219][0] = 'Y';
	grammata[219][1] = dialytika;
	grammata[250][0] = 'i';
	grammata[250][1] = dialytika;
	grammata[251][0] = 'y';
	grammata[251][1] = dialytika;
	grammata[192][0] = 'i';
	grammata[192][1] = tonos;
	grammata[192][2] = dialytika;
	grammata[224][0] = 'y';
	grammata[224][1] = tonos;
	grammata[224][2] = dialytika;
	grammata[238][0] = 'k';
	grammata[238][1] = 's';
	grammata[248][0] = 'p';
	grammata[248][1] = 's';
	grammata[206][0] = 'K';
	grammata[206][1] = 'S';
	grammata[216][0] = 'P';
	grammata[216][1] = 'S';
}

void printgramma(int gramma){

    char grammata[256][3];
    pinakas(grammata);

    if(grammata[gramma][0] != '\0'){
		putchar(grammata[gramma][0]);
		if(grammata[gramma][1] != '\0'){
			putchar(grammata[gramma][1]);
			if(grammata[gramma][2] != '\0')
				putchar(grammata[gramma][2]);
		}
	}
}

/*synarthseis allagis katastasewn fsm*/
/*default periptwsh gia ola ta grammata*/
enum fsm dflt(int gramma){
	switch (gramma){
		case 204:/*M*/
			return mkef;
		case 236:/*m*/
			return mmikr;
		case 205:/*N*/
			return nkef;
		case 237:/*n*/
			return nmikr;
		default:
			printgramma(gramma);
			return any;
   }
}
/*an to next gramma einai M kef*/
enum fsm M(int gramma){
    switch(gramma){
        case 208:/*P kef*/
			printgramma(66); /* B kef*/
			return any;
		case 240:/* p mikr*/
			printgramma(66); /* B kef*/
			return any;
		default:
			printgramma(204); /* M kef*/
			printgramma(gramma);
			return any;
	}
}

/*an to next gramma einai m mikro*/
enum fsm m(int gramma){
    switch(gramma){
        case 208:/*P kef*/
            printgramma(98); /* b*/
            return any;
    	case 240:/* p mikr*/
            printgramma(98); /* b*/
            return any;
        default:
            printgramma(236); /* m mikr*/
            printgramma(gramma);
            return any;
        }
}

/*an to next gramma einai N kef*/
enum fsm N(int gramma){
    switch(gramma){
        case 212:/*T kef*/
            printgramma(68); /* D kef*/
            return any;
        case 244:/*t mikr*/
            printgramma(68); /* D kef*/
            return any;
        default:
            printgramma(205); /* N kef*/
            printgramma(gramma);
            return any;
        }
}

/*an to next gramma einai n mikro*/
enum fsm n(int gramma){
    switch(gramma){
        case 212:/*T kef*/
            printgramma(100); /* d mikr*/
            return any;
        case 244:/*t mikr*/
                printgramma(100); /* d mikr*/
                return any;
        default:
            printgramma(237); /* n mikr*/
            printgramma(gramma);
            return any;
        }
}



int main(void){
	enum fsm (*action[])(int gramma) =  {dflt,M,N,m,n}; /*arxikopoiei ton pinaka action[] twn pointers se synarthseis*/
	int gramma;
    state = any;	/*arxikopoihsh katastashs san opiadhpote katastash*/
    while((gramma = getchar())!=EOF) {
		state = action[state](gramma); /*kalei to katallhlo state analoga me thn eisodo to gramma dhladh*/
	}
    return 0;
}
