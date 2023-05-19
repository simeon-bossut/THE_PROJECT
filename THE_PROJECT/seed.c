#include "seed.h"

int factorial(int n)
{
	if (n == 0)
		return 1;
	else
		return n * factorial(n - 1);
}

int line_to_id(char*line,int dim)
{
	//Il faut idéalement mettre un char ne contenant que des chiffres différent(ligne d'un carré latin)
int val = 0;//Ce char va être transformé à la fin en char grace to itoa

int factor = factorial(dim - 1);

val += ((line[0] - 48) - 1) * factor + 1; //Le 6 vient du fait de 3! possibilités une fois le char[0] fixé
if (dim == 3)
{
	if (line[1] > line[2])
	{
		val += 1;
	}
}
else if (dim == 4)

{
	if (line[1] > line[2]) //C des trucs que j'ai trouvé, demandez si vous voulez comprendre
	{
		val += 2;
	}
	if (line[2] > line[3])
	{
		val += 1;
	}
	if (line[1] > line[3]) //trust the process
	{
		val += 2;
	}
}
else if (dim == 5)
{
	char tab[6] = { 0 };
	int compt = 0;
	for (int i = 0;i < dim;++i)
	{
		if ((i + 1) + 48 != line[0])
		{
			tab[compt] = (i + 1) + 48;
			compt++;
		}
	}

	for (int i = 0;i < dim - 1;++i)
	{
		if (tab[i] == line[1])
		{
			val += i * 6;
		}
	}

	if (line[3] > line[4])
	{
		val += 1;
	}

	if (line[2] > line[3])
	{
		val += 2;
	}

	if (line[2] > line[4])
	{
		val += 2;
	}


}
//C fini ! Plutôt simple dans ce sens...
char Id[4] = { 0 };//3 chiffres max + \0
return val;
}

char* id_to_line(int val, int dim)//Uniquement en 4*4 pour l'instant
{                       //Parti pour la galère
	val = val % (factorial(dim));
	if (val == 0)
	{
		val = factorial(dim);
	}

	char* line = malloc(sizeof(char) * (dim + 1));//pour l'intant 4 (+\0)car taille de la ligne, par le futur malloc car taille variable
	if (line == NULL)
	{
		return NULL;
	}
	for (int i = 0;i < dim+1;++i)
	{
		line[i] = 0;
	}

	line[0] = ((val-1) / factorial(dim - 1)+1) + 48;//N'hésitez pas à poser des questions

	char* tab = malloc(sizeof(char) * (dim));//tableau contenant tous les chiffres sauf celui dans line[0]
	if (tab == NULL)
	{
		return NULL;
	}

	tab[dim - 1] = 0;

  int compt = 0;

	for (int i = 0;i < dim;++i)
	{
		if ((i + 1) + 48 != line[0])
		{
			tab[compt] = (i + 1) + 48;
			compt++;
		}
	}

	if (dim == 3)
	{
		for (int i = 0;i < dim - 1;++i)
		{
				if (line[2 - val % 2] == 0)//Si cette case déja remplie déja remplie
				{
					line[2 - val % 2] = tab[i];
				}
				else if(line[1 + val % 2]==0)
				{
					line[1 + val % 2] = tab[i];
				}
		}
		return line;
	}

	if (dim == 4)
	{
		line[1] = tab[((val - 1) % 6 / 2)];//Chiant à expliquer en commentaires(étude de la ligne de longueur 6)
	}

	if (dim==5)
	{
		line[1] = tab[((val - 1) % 24 / 6)];

		for (int i = ((val - 1) % 24 / 6);i < dim - 1;i++)//suppresion de line[1] dans tab et décalage adapté
		{
			tab[i] = tab[i + 1];
		}
		tab[dim - 2] = '\0';
    }

	if (dim == 4)
	{
		for (int i = 0;i < dim-1;++i)
		{
			if (tab[i] != line[1])//Si le chiffre est encore dispo
			{
				if (line[3 - val % 2] == 0)//Si cette case déja remplie déja remplie
				{
					line[3 - val % 2] = tab[i];
				}
				else if(line[2 + val % 2]==0)
				{
					line[2 + val % 2] = tab[i];
				}
			}
		}
	}

	if (dim == 5)
	{
		line[2] = tab[(val - 1) % 6 / 2];

		for (int i = 0;i < dim - 1;++i)
		{
			if (tab[i] != line[2])//Si le chiffre est encore dispo
			{
				if (line[4 - val % 2] == 0)//Si cette case déja remplie déja remplie
				{
					line[4 - val % 2] = tab[i];
				}
				else if(line[3 + val % 2]==0)
				{
					line[3 + val % 2] = tab[i];
				}
			}
		}
	}
	return line;
}

char*create_seed(int difficulty,int dim)
{
	int size;
	if (dim == 3)
	{
		size = 12;
	}
	else if(dim==4)
	{
		size = 20;
	}
	else if(dim==5)
	{
		size = 32;
	}
	else 
	{
		return NULL;
	}
	char* SEED = malloc(sizeof(char) * size);
	if(SEED==NULL)
	{
		return NULL;
	}
	SEED[0] = dim + 48;
	for (int i = 0;i < dim;i++)
	{
		;
	}
}

