#include "seed.h"



char* line_to_id(char*line)//Uniquement en 4*4 pour l'instant
{
	//Il faut idéalement mettre un char ne contenant que des chiffres différent(ligne d'un carré latin)
	int val = 0;//Ce char va être transformé à la fin en char grace to itoa

	val += (line[0] - 1) * 6;//Le 6 vient du fait de 3! possibilités une fois le char[0] fixé

	if (line[1] > line[2])//C des trucs que j'ai trouvé, demandez si vous voulez comprendre
	{
		val += 2;
	}
	if (line[2] > line[3])
	{
		val += 1;
	}
	if (line[1] > line[3])//trust the process
	{
		val += 2;
	}
	//C fini ! Plutôt simple dans ce sens...
	char Id[4]={0};//3 chiffres max + \0
	_itoa_s(val, Id,3, 10);
	return Id;
}

char* id_to_line(char* Id)//Uniquement en 4*4 pour l'instant
{                       //Parti pour la galère
	int val = atoi(Id); //Passage par les int pour simplifier des calculsy

	char line[5]={0};//pour l'intant 4 (+\0)car taille de la ligne, par le futur malloc car taille variable

	line[0] = ((val / 6) + 1)+48;//N'hésitez pas à poser des questions

	char tab[4]={0};//tableau contenant tous les chiffres sauf celui dans line[0]

	int compt = 0;

	for (int i = 0;i < 4;++i)
	{
		if ((i + 1)+48 != line[0])
		{
			tab[compt] = (i + 1)+48;
			compt++;
		}
	}


	line[1]=tab[(val%6-1)/2];//Chiant à expliquer en commentaires

	
	for(int i=0;i<3;++i)
	{
		if(tab[i]!=line[1])//Si le chiffre est encore dispo
		{ 
			if (line[3 - val % 2] == 0)//Si cette case déja remplie déja remplie
			{
				line[3 - val % 2] = tab[i];
			}
			else
			{ 
				line[2+ val % 2]= tab[i];
			}
		}
	}
	return line;
}