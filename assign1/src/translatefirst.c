/* SFAKIANAKIS STYLIANOS csd4513*/

#include <stdio.h>

#define tonos 39
#define dialytika 34


enum fsm{any, M_cap, N_cap, m_small, n_small}state; /*dhlwsh katastasewn fsm*/


void gemismapinaka(char letters[256][3])
{
    int i = 0,j = 0;
	char smalls[25] = {'a','v','g','d','e','z','h','8','i','k','l','m','n','j','o','p','r','s','s','t','y','f','x','y','w'}; /* 2o s gia to s teliko*/
	char caps[24] = {'A','V','G','D','E','Z','H','8','I','K','L','M','N','J','O','P','R','S','S','T','Y','F','X','Y','W'};

   	for(i = 0; i < 256; i++){
		letters[i][0] = i;
		letters[i][1] = '\0';
		letters[i][2] = '\0';
	}

	/*mikra*/
	for(i = 225; i < 251; i++){
		letters[i][0] = smalls[j];
		j++;
	}

    /*kefalaia*/
    j=0;
	for(i = 193; i <218; i++){
		letters[i][0] = caps[j];
		j++;
	}

	/*mikra me '*/
	letters[220][0] = 'a';
	letters[220][1] = tonos;
	letters[221][0] = 'e';
	letters[221][1] = tonos;
	letters[222][0]  = 'h';
	letters[222][1] = tonos;
	letters[223][0] = 'i';
	letters[223][1] = tonos;
	letters[252][0] = 'o';
	letters[252][1] = tonos;
	letters[253][0] = 'y';
	letters[253][1] = tonos;
	letters[254][0] = 'w';
	letters[254][1] = tonos;
	/*kefalaia me '*/
	letters[182][0] = 'A';
    letters[182][1] = tonos;
	letters[184][0] = 'E';
	letters[184][1] = tonos;
	letters[185][0] = 'H';
	letters[185][1] = tonos;
	letters[186][0] = 'I';
	letters[186][1] = tonos;
	letters[188][0] = 'O';
	letters[188][1] = tonos;
	letters[190][0] = 'Y';
	letters[190][1] = tonos;
	letters[191][0] = 'W';
	letters[191][1] = tonos;
	/*dialitika*/
	letters[218][0] = 'I';
	letters[218][1] = dialytika;
	letters[219][0] = 'Y';
	letters[219][1] = dialytika;
	letters[250][0] = 'i';
	letters[250][1] = dialytika;
	letters[251][0] = 'y';
	letters[251][1] = dialytika;
	letters[192][0] = 'i';
	letters[192][1] = tonos;
	letters[192][2] = dialytika;
	letters[224][0] = 'y';
	letters[224][1] = tonos;
	letters[224][2] = dialytika;
	letters[238][0] = 'k';
	letters[238][1] = 's';
	letters[248][0] = 'p';
	letters[248][1] = 's';
	letters[206][0] = 'K';
	letters[206][1] = 'S';
	letters[216][0] = 'P';
	letters[216][1] = 'S';
}

void printstate(int c)
{
    char letters[256][3];
    gemismapinaka(letters);

    if(letters[c][0] != '\0'){
		putchar(letters[c][0]);
		if(letters[c][1] != '\0'){
			putchar(letters[c][1]);
			if(letters[c][2] != '\0')
				putchar(letters[c][2]);
		
		}
	}
}

/*synarthseis allagis katastasewn*/
enum fsm dflt(int c)
{
   switch (c){
		case 204:/*M el*/
			return M_cap;
			break;
		case 236:/*m el*/
			return m_small;
			break;
		case 205:/*N el*/
			return N_cap;
			break;
		case 237:/*n el*/
			return n_small;
			break;
		default:
			printstate(c);
			return any;
			break;

   }
}
enum fsm M(int c)
{
    switch(c)
    {
        case 208:/*P el*/
			printstate(66); /* B caps*/
			return any;
			break;
		case 240:/* p el*/
			printstate(66); /* B caps*/
			return any;
			break;
		case 204:/*M el*/
			printstate(204); /* M el*/
			return M_cap;
			break;
		case 236:/*m el*/
			printstate(204); /* M  el*/
			return m_small;
			break;
		case 205:/*N el*/
			printstate(204); /* M el*/
			return N_cap;
			break;
		case 237:/*n el*/
			printstate(204); /* M el*/
			return n_small;
			break;
		default:
			printstate(204); /* M el*/
			printstate(c);
			return any;
			break;
	}
}


enum fsm N(int c)
{
        switch(c)
        {
                case 212:/*T el*/
                        printstate(68); /* D caps*/
                        return any;
                        break;
                case 244:/*t el*/
                        printstate(68); /* D caps*/
                        return any;
                        break;
                case 205:/*N el*/
                        printstate(205); /* N el*/
                        return N_cap;
                        break;
                case 237:/*n el*/
                        printstate(205); /* N el*/
                        return n_small;
                        break;
                case 204:/*M el*/
                        printstate(205); /* N el*/
                        return M_cap;
                        break;
                case 236:/*m el*/
                        printstate(205); /* N el*/
                        return m_small;
                        break;
                default:
                        printstate(205); /* N el*/
                        printstate(c);
                        return any;
                        break;
        }
}


enum fsm m(int c)
{
        switch(c)
        {
                case 208:/*P el*/
                        printstate(98); /* b*/
                        return any;
                        break;
                case 240:/* p el*/
                        printstate(98); /* b*/
                        return any;
                        break;
                case 204:/*M el*/
                        printstate(236); /* m el*/
                        return M_cap;
                        break;
                case 236:/*m el*/
                        printstate(236); /* m el*/
                        return m_small;
                        break;
                case 205:/*N el*/
                        printstate(236); /* m el*/
                        return N_cap;
                        break;
                case 237:/*n el*/
                        printstate(236); /* m el*/
                        return n_small;
                        break;
                default:
                        printstate(236); /* m el*/
                        printstate(c);
                        return any;
                        break;
        }
}

enum fsm n(int c)
{
        switch(c)
        {
                case 212:/*T el*/
                        printstate(100); /* d*/
                        return any;
                        break;
                case 244:/*t el*/
                        printstate(100); /* d*/
                        return any;
                        break;
                case 204:/*M el*/
                        printstate(237); /* n el*/
                        return M_cap;
                        break;
                case 236:/*m el*/
                        printstate(237); /* n el*/
                        return m_small;
                        break;
                case 205:/*N el*/
                        printstate(237); /* n el*/
                        return N_cap;
                        break;
                case 237:/*n el*/
                        printstate(237); /* n el*/
                        return n_small;
                        break;
                default:
                        printstate(237); /* n el*/
                        printstate(c);
                        return any;
                        break;
        }
}


enum fsm (*action[])(int c) =  {dflt,M,N,m,n};

int main(void)
{
    state = any;/*arxikopoihsh katastashs san opiadhpote katastash*/
    int c;

    while((c = getchar())!=EOF)
    {
		state = (action[state])(c);
	}
    return 0;
}
