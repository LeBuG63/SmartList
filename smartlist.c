#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <float.h>
#include <math.h>

enum	suitType_e
{
	UNKNOW,
	CONSTANT,
	GEOMETRIC,
	ARITHMETIC
};

typedef enum suitType_e	suitType_t;

int essentiallyEqual(float a, float b)
{
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON);
}

int definitelyGreaterThan(float a, float b)
{
    return (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON);
}

int definitelyLessThan(float a, float b)
{
    return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON);
}

// Cette fonction sert à récuperer les nombres dans une chaîne de caractères
int	get_numbers(char *pStrOperation, float *fTabSuit)
{
	unsigned int 	k = 0;
	char 			*pch = NULL;

	pch = strtok(pStrOperation, ", -+");

	while(pch != NULL)
	{
		fTabSuit[k++] = atof(pch);

		pch = strtok(NULL, ", -+");
	}

	return k;
}

// Cette fonction analyse le type de suite que l'utilisateur a rentrée
suitType_t get_suit_type(float *fTabSuit, size_t nNumbersInTab)
{
	size_t 	index;
	float 	tmp;
	int 	err = 0;

	tmp = fTabSuit[0];
	for(index = 1; index < nNumbersInTab && err != 1; ++index) // On va vérifier si les nombres sont "CONSTANT"
	{
		if(!essentiallyEqual((fTabSuit[index]), tmp))
			err = 1;
	}

	if(!err) return CONSTANT; err = 0;

	tmp = fTabSuit[1] - fTabSuit[0];
	for(index = 2; index < nNumbersInTab && err != 1; ++index) // On va vérifier si les nombres sont "ARITHMETIC"
	{
		if(!essentiallyEqual((fTabSuit[index] - fTabSuit[index - 1]), tmp))
			err = 1;
	}

	if(!err) return ARITHMETIC; err = 0;

	tmp = fTabSuit[1] / fTabSuit[0];
	for(index = 2; index < nNumbersInTab && err != 1; ++index) // On va vérifier si les nombres sont "GEOMETRIC"
	{
		if(!essentiallyEqual((fTabSuit[index] / fTabSuit[index - 1]), tmp))
			err = 1;
	}

	if(!err) return GEOMETRIC; err = 0;

	return UNKNOW;
}

// Cette fonction continue la suite logique
void continue_suit(suitType_t suitType, float *fTabSuit, size_t numbersToPrint)
{
	size_t 	index;
	float 	factor;
	float 	value;

	switch(suitType)
	{
	case ARITHMETIC:
		factor 	= fTabSuit[1] - fTabSuit[0];
		value 	= fTabSuit[0];

		for(index = 1; index < numbersToPrint; ++index)
		{
			printf("%.3f|", value);
			value += factor;
		}

		break;
	case GEOMETRIC:
		factor 	= fTabSuit[1] / fTabSuit[0];
		value 	= fTabSuit[0];

		for(index = 1; index < numbersToPrint; ++index)
		{
			printf("%.3f|", value);
			value *= factor;
		}
		break;

	case CONSTANT:
		value = fTabSuit[0];
		for(index = 1; index < numbersToPrint; ++index)
			printf("%f|", value);
		break;

	case UNKNOW:
		printf("Il n'y a aucune suite logique trouvee.\n");
		break;

	default:
		break;
	}
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "Erreur: il faut 3 arguments.");
		return 2;
	}
	size_t 		numbersToPrint = atoi(argv[1]);
	size_t 		sizeStringOperation = strlen(argv[2]);
	float 		*fTabSuit = malloc(sizeStringOperation * sizeof(float));
	int 		nNumbers;
	suitType_t	suitType;

	if(fTabSuit == NULL)
	{
		fprintf(stderr, "Erreur: memoire allouee indisponible");
		return 1;
	}

	nNumbers = get_numbers(argv[2], fTabSuit);

	suitType = get_suit_type(fTabSuit, nNumbers);

	continue_suit(suitType, fTabSuit, numbersToPrint);

	free(fTabSuit);

    return 0;
}
