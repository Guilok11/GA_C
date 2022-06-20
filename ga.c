#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>


#define low -2.00
#define high 2.00
#define TAM_POP 10
#define num_fathers 2


double GEN_POP(double low, double high) {
    return low + (rand() / (RAND_MAX / (high - low)));
}


double* fitness(double x[TAM_POP], double y[TAM_POP]) {
    int i;
    double* fitness_value = malloc(sizeof(double) * TAM_POP);

	printf("\nFitness: ");
    for (i = 0; i < TAM_POP; i++) {
        fitness_value[i] = -(100 * ((x[i] * x[i] - y[i]) * (x[i] * x[i] - y[i])) + ((1 - x[i]) * (1 - x[i])));
        printf("%f ", fitness_value[i]);
    }

    return fitness_value;
}

//Convert fitness to positive value
double* convert_fitness(double fitness_value[TAM_POP]) {
    int i;

	printf("\nNew Fitness: ");
    for (i = 0; i < TAM_POP; i++) {
        fitness_value[i] = -1 / fitness_value[i];
        printf("%f ", fitness_value[i]);
    }

    return fitness_value;
}

double sum_fitness(double fitness_value[TAM_POP]) {
    int i;
    double total_fitness = 0;

	printf("\nFitness Sum: ");
    for (i = 0; i < TAM_POP; i++) {
        total_fitness += fitness_value[i];
		printf("%f ", total_fitness);
    }

    return total_fitness;
}

double* check_percentage(double fitness_value[TAM_POP], double total_fitness) {
    int i;
    double* percent_fitness = malloc(sizeof(double) * TAM_POP);

	printf("\nPercent: ");
    for (i = 0; i < TAM_POP; i++) {
		percent_fitness[i] = (fitness_value[i] / total_fitness) * 100;
        printf("%f ", percent_fitness[i]);
    }

    return percent_fitness;
}

double* check_sum_percent_fitness(double percent_fitness[TAM_POP]) {
	int i;
    double* sum_percent_fitness = malloc(sizeof(double) * TAM_POP);
	double sum = 0;
	printf("\nSum: ");
    for (i = 0; i < TAM_POP; i++) {
        sum += percent_fitness[i];
		sum_percent_fitness[i] += sum;
		printf("%f ", sum_percent_fitness[i]);
    }

    return sum_percent_fitness;
}

double roulette_select_method() {
	int i;
	double drawn_value;
	drawn_value = rand() % 100;
	return drawn_value;
}

double crossing_geometric_mean (double father_1, double father_2) {
    double offspring;

    offspring = sqrt((pow(father_1, 2)) * (pow(father_2, 2)));

    return offspring;
}

double mutate(int TAM_POP, int low, int high) {

}

int elitism(double fitness_value[TAM_POP]) {
	int position, i, max_value = -99999;

	for(i = 0; i < TAM_POP; i++) {
		if(fitness_value[i] > max_value) {
			max_value = fitness_value[i];
			position = i;
		}
	}
	return position;
}

int main() {
	srand(time(NULL));

    int i, j, k, aux_different_position, position_best_idx_elitism;
    double x, y, total_fitness, offspring;
	double population_X[TAM_POP], population_Y[TAM_POP];
    double Roulette_Value, auxPopX[TAM_POP], auxPopY[TAM_POP];
    double paisX[num_fathers], paisY[num_fathers];
	double* fitness_value = malloc(sizeof(double) * TAM_POP);
	double* aux_value_fitness = malloc(sizeof(double) * TAM_POP);
    double* percent_fitness = malloc(sizeof(double) * TAM_POP);
    double* sum_percent_fitness = malloc(sizeof(double) * TAM_POP);

    //Generate the population of individuals with x,y chromosomes
	printf("Pop:");
    for (i = 0; i < TAM_POP; i++) {
        population_X[i] = GEN_POP(low, high);
        population_Y[i] = GEN_POP(low, high);
        printf("\n x[%d] = %f           y[%d] = %f", i + 1, population_X[i], i + 1, population_Y[i]);
    }

    //Calculate the fitness    
	fitness_value = fitness(population_X, population_Y);
    convert_fitness(fitness_value);

	//Fitness Sum
	total_fitness = sum_fitness(fitness_value);

    //Calculate percent
    percent_fitness = check_percentage(fitness_value, total_fitness);
    sum_percent_fitness = check_sum_percent_fitness(percent_fitness);
    position_best_idx_elitism = elitism(fitness_value);

	//Generate New Pop
	for(i = 0; i < TAM_POP; i++) {
		if(i == position_best_idx_elitism) {
			population_X[0] = population_X[i];
			population_Y[0] = population_Y[i];
			fitness_value[0] = fitness_value[i];
		}
	}
	//Selection 
	printf("\nFathers: ");
	for(i = 0; i < TAM_POP; i++) {
		for(j = 0; j < num_fathers; j++) {
			Roulette_Value = roulette_select_method();
			printf("\n\nDrawn Value: %f", Roulette_Value);
			for(k = 0; k < TAM_POP; k++) {
				if(Roulette_Value < sum_percent_fitness[k] && aux_different_position != k) {
					aux_different_position = k;
					printf("\nIdx: %d", k - 1);
					auxPopX[i] = population_X[k - 1];
					auxPopY[i] = population_Y[k - 1];
					aux_value_fitness[i] = fitness_value[k - 1];
					printf("\n%f %f %f", auxPopX[i], auxPopY[i], aux_value_fitness[i]);
					k = TAM_POP;
				}
			}
			paisX[j] = auxPopX[i];
			paisY[j] = auxPopY[i];
		}
	}
	for(i=0;i<TAM_POP;i++){
        printf("\nChromosomes of father_X: %f",auxPopX[i]);
	}
    
    return 0;
}

