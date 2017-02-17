#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 12001

int nraparitii(char *sir, char *cuvant)
{
	char *p;
	int count = 0;
	p = strtok(sir," ,'!?\"");
	while (p != NULL)
	{
       if(strcmp(p,cuvant) == 0)
       		count++;

    	p = strtok(NULL," ,'!?\"");
	}

	return count;
}


char* inlocuire(char *sir, char *de_inlocuit, char *secventa)
{	
	char *copie = strdup(sir);
	int aparitii = nraparitii(copie, de_inlocuit);
	
	char *aux;

	if(strlen(secventa) > strlen(de_inlocuit))
		aux = (char*)malloc(max + (strlen(secventa) - strlen(de_inlocuit))*
				aparitii + 1);
		
	else
		aux = (char*)malloc (max*sizeof(char));

	
	if(aux == NULL)
		return 0;

	char *p;
	p = strstr(sir,de_inlocuit);

	while (p != NULL)
	{	 
		int m = p-sir;
		int sw=0; int t= 0; // t=taiere

		int l = strlen(de_inlocuit);
		
		strncat(aux, sir, m);
		
		//testam daca secventa ce trebuie inlocuita este cuvant si realizam 
		//inlocuirea intr-un sir auxiliar
			if((m == 0) && (sir[m+l] == ' '|| sir[m+l] == ',' || sir[m+l] == '?'
				|| sir[m+l] == '!' || sir[m+l] == '\'' || sir[m+l] == '"' 
				|| sir[m+l] == '\0'))
		{
			strcat(aux, secventa);
		}
		
		else
		{
			if((sir[m-1] == ' '|| sir[m-1] == ',' || sir[m-1] == '?'|| sir[m-1] == '!' 
				|| sir[m-1] == '\'' || sir[m-1] == '"') && (sir[m+l] == '\0' 
				|| sir[m+l] == ' ' || sir[m+l] == ',' || sir[m+l]=='?' 
				|| sir[m+l]== '!' || sir[m+l]=='\'' || sir[m+l]=='"'))
				{	
					sw = 1;
				}
			else
			{
				while(sir[m+l+t] != '\0' && sir[m+l+t] != ' ' && sir[ m+l+t] != ',' && 
					sir[m+l+t]!='?' && sir[m+l+t] != '!' 
					&& sir[m+l+t]!='\'' && sir[m+l+t]!='"')
				{
					t ++;
				}
			}
		
			if(sw == 0)
			{
				strncat(aux, p, l+t);
			}
			else
				strcat(aux, secventa);
	    }

		sir = p + t + strlen(de_inlocuit);
		p = strstr(sir, de_inlocuit);

	}
	

	strncat(aux, sir, p-sir);
	

return aux;

}

char * permuta(int k, char *sir)
{	
	char *p1 = sir;
	char *p2 = strpbrk(sir, " ,?!\"'");
	
	while(p2 != NULL)
	{
		if(p2 - p1 <= 0)
			p2 = strpbrk(p2 + 1, " ,?!\"'");
		else if(strchr(" ,?!\"'", *p1) != NULL)
			p1 = p1 + 1;
		else if(p2 - p1 > 0)
		{
			char *aux;

			aux = (char*)malloc(max * sizeof(char));
			strncpy(aux, p1, p2 - p1);
			
			int k1,m;
			k1 = k % strlen(aux);
			m = strlen(aux);

			strncat(aux + m - k1, aux, m - k1);
			strcpy(aux, aux + m -k1);
			strcat(aux, p2);
			strcpy(p1, aux);
			
			p1 = p2;
			p2 = strpbrk(p2 + 1, " ,?!\"'");
				
		}
		

	}

	while(strchr(" ,?!\"'", *p1) != NULL && p1 != NULL)
		p1 = p1 + 1;
	
	if(p1 != NULL)
	{		
		char * aux;	
		aux = (char*)malloc(max * sizeof(char));
		
		strcpy(aux, p1);
		int k1,m;
		
		m = strlen(aux);
		k1 = k % m;

		strncat((aux + m - k1), aux, m - k1);
		strcpy(aux, aux + m - k1);
		strcpy(p1, aux);
	}
	
	return sir;
	
}



int main()
{
	int N,M,i;
	
	
	scanf("%d", &N);
	getchar();
	

	char **linie = (char**)malloc(N*sizeof(char*));
	

	for(i=0; i < N; i++)
	{	
		linie[i] = (char*) calloc (max,sizeof(char));
		if(linie[i] == NULL)
			return 0;
		
	}

	for(i=0; i<N; i++)
	{
		fgets(linie[i], max, stdin);
		linie[i][strlen(linie[i]) - 1] = '\0';
		
	}


	
	scanf("%d", &M);
	

	while(M > 0)
	{
		int operatie;
		scanf("%d", &operatie);

		switch (operatie)
		{
			case 1:
			
			fgetc(stdin);

			char *cuvant = (char*)malloc(sizeof(char)*max);
			if(cuvant == NULL)
				return 0;

			scanf("%s", cuvant);

			int count = 0;
			
			for (i = 0; i < N; i++)
			{	
				char *aux;

				aux = strdup(linie[i]);	
				
				count = count + nraparitii(aux, cuvant);
			}

			printf("%d\n", count);
			
			break;

			case 2:

			fgetc(stdin);

			char *de_inlocuit = (char*)malloc(sizeof(char)*max);
			if(de_inlocuit == NULL)
				return 0;
			
			scanf("%s", de_inlocuit);
			
			fgetc(stdin);

			char *secventa = (char*)malloc(max*sizeof(char));
			if(secventa == NULL)
					return 0;
			
			scanf("%s", secventa);

			for(i=0; i<N; i++)

			{	if(strlen(linie[i]) > 11998 && (strlen(secventa) > strlen(de_inlocuit)))
				{
					char *p;
					p = (char*)realloc(linie[i], max * 2 * sizeof(char) + 1);
					if(p != NULL){
						linie[i] = p;
				
					}
				}		
			}

			for(i=0; i<N; i++)
			{
				char * aux = strdup(linie[i]);
				linie[i] = inlocuire(aux, de_inlocuit, secventa);
				puts(linie[i]);
			
			}

			//free(secventa);
			//free(de_inlocuit);
			 
			break;

			case 3:
			
			fgetc(stdin);


			int k;
			scanf("%d", &k);

			for(i=0; i<N; i++)
			{
				
				strcpy(linie[i], permuta(k, linie[i]));
				printf("%s\n", linie[i]);
				
			}


			break;

			default:

			break;
		}


		M--;
	}

/*for(i=0; i <N; i++)
{	
	free(linie[i]);
}

free(linie);*/

return 0;
}
