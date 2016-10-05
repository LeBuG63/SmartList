#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <float.h>
#include <math.h>

enum	e_sequence_type {
	UNKNOW,
	CONSTANT,
	GEOMETRIC,
	ARITHMETIC
};

typedef enum e_sequence_type	t_sequence_type;

static int essentiallyEqual(float a, float b) {
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON);
}

int	get_string_carac_numbers(char *str_opt, float *array_sequence)
{
	unsigned 	n_carac 	= 0u;
	char 		delimiters[] 	= ", -+";
	char 		*pch 		= NULL;

	pch = strtok(str_opt, delimiters);

	while(pch != NULL) {
		array_sequence[n_carac++] = atof(pch);

		pch = strtok(NULL, delimiters);
	}

	return n_carac;
}

t_sequence_type get_sequence_type(float *array_sequence, size_t n_elem) {
	size_t 	index;
	float 	tmp;
	int 	err = 0;

	tmp = array_sequence[0];
	for(index = 1; index < n_elem && err != 1; ++index) { // Si les nombres sont "CONSTANT"
		if(!essentiallyEqual((array_sequence[index]), tmp))
			err = 1;
	}

	if(!err) return CONSTANT; err = 0;

	tmp = array_sequence[1] - array_sequence[0];
	for(index = 2; index < n_elem && err != 1; ++index) { // Si les nombres sont "ARITHMETIC"
		if(!essentiallyEqual((array_sequence[index] - array_sequence[index - 1]), tmp))
			err = 1;
	}

	if(!err) return ARITHMETIC; err = 0;

	tmp = array_sequence[1] / array_sequence[0];
	for(index = 2; index < n_elem && err != 1; ++index) { // Si les nombres sont "GEOMETRIC"
		if(!essentiallyEqual((array_sequence[index] / array_sequence[index - 1]), tmp))
			err = 1;
	}

	if(!err) return GEOMETRIC; err = 0;

	return UNKNOW;
}

void continue_sequence(t_sequence_type sequenceType, float *array_sequence, size_t n_to_print) {
	unsigned 	index;
	float 		factor;
	float 		value;

	switch(sequenceType)
	{
	case ARITHMETIC:
		factor 	= array_sequence[1] - array_sequence[0];
		value 	= array_sequence[0];

		printf("Type: Arithmetique\nRaison: %f\n\n", factor);

		for(index = 1; index < n_to_print; ++index) {
			printf("[%u] %.3f\n", index, value);
			value += factor;
		}
		break;
	case GEOMETRIC:
		factor 	= array_sequence[1] / array_sequence[0];
		value 	= array_sequence[0];

		printf("Type: Geometrique\nRaison: %f\n\n", factor);

		for(index = 1; index < n_to_print; ++index) {
			printf("[%u] %.3f\n", index, value);
			value *= factor;
		}
		break;

	case CONSTANT:
		value = array_sequence[0];

		printf("Type: Constante\n\n");

		for(index = 1; index < n_to_print; ++index)
			printf("[%u] %.3f\n", index, value);
		break;

	case UNKNOW:
		printf("Il n'y a aucune sequence logique trouvee.\n");
		break;

	default:
		break;
	}
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Erreur: il faut 3 arguments.");
		return 1;
	}

	t_sequence_type	sequence_type;

	size_t 		n_to_print 	= (unsigned)atoi(argv[1]);
	size_t 		size_string_ope = strlen(argv[2]);
	float 		*array_sequence	= malloc(size_string_ope * sizeof(float));
	int 		n;

	if(array_sequence == NULL) {
		fprintf(stderr, "Erreur: memoire allouee indisponible");
		return 1;
	}

	n = get_string_carac_numbers(argv[2], array_sequence);

	sequence_type = get_sequence_type(array_sequence, n);

	continue_sequence(sequence_type, array_sequence, n_to_print);

	free(array_sequence);

    return 0;
}
