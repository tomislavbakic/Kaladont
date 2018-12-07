#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct kaladont{
    char *rec;
    struct kaladont *sledeci;
}lista;

int broj_reci = 1; //global

void dodaj(lista **p, char rec[]){
    lista *t,*novi;
    t = *p;
    
    novi = (lista*) malloc (sizeof(lista));
    if (novi == NULL)
    {
        printf("Greska pri alokaciji memorije\n\a");
        exit(1);
    }
    novi->rec = (char*) malloc ((strlen(rec)+1)*sizeof(char));
    rec[strlen(rec)]='\0';
    strcpy(novi->rec,rec);
    //dodajemo na pocetak liste nove elemente
    if (t == NULL)
    {
        novi->sledeci = NULL;
    }
    else
    {
        novi->sledeci = t;
    }
    broj_reci++; //broj reci se povecao za jedan
    *p = novi; //promenjena glava liste
}

void stampaj_reci(lista *p){
	printf("Reci u igri: \n\n");
	while(p)
	{
		printf("%s\n",p->rec);
		p = p->sledeci;
	}
}

int provera(lista *p,char rec[]){
	char poslednja_dva[3];
	char prva_dva[3];
	char ka_slova[3];
	
	ka_slova[2] = rec[strlen(rec)];
	ka_slova[1] = rec[strlen(rec)-1];
	ka_slova[0] = rec[strlen(rec)-2];
	
	if(strcmp(ka_slova,"ka") == 0) 
	{
		printf("KALADONT!\nIgra je gotova!\n");
		return 2;
	}
		
	if(p == NULL)
	{
		return 1;
	}
	else
	{
		poslednja_dva[2] = p->rec[strlen(p->rec)];
		poslednja_dva[1] = p->rec[strlen(p->rec)-1];
		poslednja_dva[0] = p->rec[strlen(p->rec)-2];
		//printf("\nposlednja dva slova prethodne reci %s\n",poslednja_dva);
		prva_dva[0] = rec[0];
		prva_dva[1] = rec[1];
		prva_dva[2] = '\0';
		//printf("\nprva dva slova nove reci %s\n",prva_dva);
		if( strcmp(poslednja_dva,prva_dva) != 0)
		{
			printf("Rec mora da pocne sa: %s \n",poslednja_dva);
			return 0;
		}
		
		while(p)
		{
			if(strcmp(rec,p->rec) == 0)
			{
				printf("Rec je vec bila, pokusaj ponovo!\n");
				return 0;
			}
			p = p->sledeci;
		}
		
		
	}
	return 1; //rec je okej	
}

int main()
{
    lista *glava=NULL; //lista reci
    char rec[30]; //nova rec
    //broj reci do sada u igri
    printf("IGRA KALADONT\n");
    int broj=0;
	//unos igraca
	int i,n; //broj igraca
    printf("Uneti broj igraca: ");
    scanf("%d",&n);
    char igrac[n][30];
	for(i=0;i<n;i++) //ucitavanje
    {
    	printf("Uneti ime %d-og igraca: ",i+1);
    	scanf("%s",igrac[i]);
	}
	for(i=0;i<n;i++) //igraci koji igraju
	{
		printf("Igrac %d je: %s\n",i+1,igrac[i]);
	}
	//uneti igraci
	printf("\nIgra moze da pocne!\n\n");
	
	int ind = 0;
    while(1)
    {
    	for(i=0;i<n;i++)
    	{
			while(ind == 0)
			{
				printf("%s je na potezu: ",igrac[i]);	
	        	scanf("%s",rec);
	        	if ( strcmp(rec,"KRAJ") == 0)
	        	{
	        			printf("\nU igri je iskorisceno %d reci\n",broj_reci);
		    			if(broj_reci < 10 )
		    				printf("Uhh, brzo... Vise srece drugi put!\n");
		    			else if (broj_reci < 25)
							printf("Nije lose, vise srece drugi put!\n");
						else
							printf("UuUuUUuuuUUu svaka cast, odlicna partija!\n");
		    			sleep(10);
		
		    			exit(1);
				}
					ind = provera(glava,rec);
					if( ind == 1)  //rec je u redu, dodaje se u listu reci
					{
						dodaj(&glava,rec);
						ind = 0;
		    			break;
					}
		    		else if (ind == 2)  //ka
		    		{
		    			printf("\nU igri je iskorisceno %d reci\n",broj_reci);
		    			if(broj_reci < 10 )
		    				printf("Uhh, brzo... Vise srece drugi put!\n");
		    			else if (broj_reci < 25)
							printf("Nije lose, vise srece drugi put!\n");
						else
							printf("UuUuUUuuuUUu svaka cast, odlicna partija!\n");
		    			sleep(10);	
		    			exit(1);
					}
					else
					{
						
					}	
					
	    	}
		}
	}
	char string[20];
	printf("Jeste li uzivali?\n");
	scanf("%s",string);
	
    return 0;
}
