#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MAX 12001

struct cuvant
{
	char *cuvant;
	int aparitii;
};

typedef struct cuvant Cuvant;

int compare(const void* a, const void* b)
{
	Cuvant cuv1 = *(const Cuvant *)a;
	Cuvant cuv2 = *(const Cuvant *)b;

	if( cuv1.aparitii < cuv2.aparitii ) 
		return 1;
	if( cuv1.aparitii > cuv2.aparitii )
		return -1;
	
	if(strcmp(cuv1.cuvant, cuv2.cuvant) > 0) 
		return 1;
	if(strcmp(cuv1.cuvant, cuv2.cuvant) < 0) 
		return -1;

	return 0;
}

int cuvinte(char *cuvant, Cuvant *cuvinte, int n)
{
	int i;
	//verificam daca cuvantul a mai fost introdus in lista

	for(i = 0; i < n; i++)
		if(strcmp(cuvant, cuvinte[i].cuvant) == 0)
			return i;

	return -1;

}

int distanta(char *cuv1, char *cuv2)

{	
	int l1 = strlen(cuv1);
	int l2 = strlen(cuv2);
	int lmin, lmax, sum = 0;

	if(l1 > l2)
	{
		lmax = l1;
		lmin = l2;
	}
	
	else
	{
		lmax = l2;
		lmin = l1;
	}

	int i;

	for(i = 0; i < lmin; i++)
		sum = sum + abs(cuv1[i] - cuv2[i]);

	if(lmin == l1)
	{
		for(i = lmin; i < lmax; i++)
			sum = sum + abs('\0' - cuv2[i]);
	}
	
	else
	{	
		for(i = lmin; i < lmax; i++)
			sum = sum + abs(cuv1[i] - '\0');	
	}

	return sum;
}

void sim(Cuvant *NR1, int l1, Cuvant *NR2, int l2)
   
  {
  	int NR = 0, i;

	if(l1 > l2)
    	NR = l2;
    else
    	NR = l1;

    int similitudine = 0;

    similitudine = 100 * abs(l1 - l2);

    for(i = 0; i < NR; i++)
    {
    	similitudine = similitudine + (NR1[i].aparitii + NR2[i].aparitii)
    	 * distanta(NR1[i].cuvant, NR2[i].cuvant);
    }	
    
    printf("%d\n", similitudine);
  } 

   int main()
   {
   	 int N,M,i;

   	scanf("%d", &N);
	getchar();

	char **text1, **text2;

	text1 = (char**)malloc(N * sizeof(char*));

	for(i = 0; i < N; i++)
	{
		text1[i] = (char*)malloc(MAX);
		
		fgets(text1[i], MAX, stdin);
		
		text1[i][strlen(text1[i]) - 1] = '\0';
	}

	scanf("%d", &M);
	getchar();

	text2 = (char**)malloc(M * sizeof(char*));

	for(i = 0; i < M; i++)
	{
		text2[i] = (char*)malloc(MAX);
		fgets(text2[i], MAX, stdin);
		text2[i][strlen(text2[i]) - 1] = '\0';
	}

	int l1 = 0, l2 = 0, pozitie;
	char *aux, *p;
	Cuvant *NR1, *NR2;

	NR1 = (Cuvant*)malloc(N * MAX * sizeof(Cuvant));
	NR2 = (Cuvant*)malloc(M * MAX * sizeof(Cuvant));

	//introducem cuvintele in liste

	for(i=0; i<N; i++)
	{
		aux = strdup(text1[i]);
		p = strtok(aux, " ?!,'\"");

		while(p != NULL)
		{
			if((pozitie = cuvinte(p, NR1, l1)) != -1)
				NR1[pozitie].aparitii ++;

			else
			{	
				NR1[l1].cuvant = strdup(p);
				NR1[l1].aparitii = 1;
				l1++;
			}
			
			p = strtok(NULL, " ?!,'\"");
		}
	}

	for(i=0; i<M; i++)
	{
		aux = strdup(text2[i]);
		p = strtok(aux, " ?!,'\"");

		while(p != NULL)
		{
			if((pozitie = cuvinte(p, NR2, l2)) != -1)
				NR2[pozitie].aparitii ++;

			else
			{	
				NR2[l2].cuvant = strdup(p);
				NR2[l2].aparitii = 1;
				l2++;
			}
			
			p = strtok(NULL, " ?!,'\"");
		}
	}

	qsort(NR1, l1, sizeof(Cuvant), compare);

    qsort(NR2, l2, sizeof(Cuvant), compare);

    sim(NR1, l1, NR2, l2);

    return 0;

   }	 