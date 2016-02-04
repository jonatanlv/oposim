#ifndef OPOSIM_H_INCLUDED
#define OPOSIM_H_INCLUDED

#include <argp.h>

typedef struct args_s {
  int temas;
  int bolas;
  int estudiados;
  int min;
  int reps;
  char rng;
} args_s;

// Valores por defecto
#define TEMAS_D 72
#define BOLAS_D 4
#define ESTUDIADOS_D 50
#define MIN_D 1
#define REPS_D 1e8
#define RNG_D '.'

// Cabeceras de las funciones
void random_init(char opc);
void random_free();
int s_experimento(int temas, int bolas, int estudiados);
int *experimento(int temas, int bolas, int estudiados, int reps);
double *frecs(int *histograma, int l);
error_t ops_parser(int argc, char **argv, args_s *arguments);

// Macros

#define Print_Probs(vector, l, min) do {				\
    double aprobado = 0, suspenso = 0;					\
    for (int i = 0; i < (l); i++) {					\
      if (i < (min)) {							\
	suspenso += vector[i];						\
      } else {								\
	aprobado += vector[i];						\
      }									\
      printf("Probabilidad de saber %d temas es %.2f %%\n", i, vector[i] * 100); \
    }									\
    printf("La probabilidad de aprobar es %.2f %%\n", aprobado * 100);	\
    printf("La probabilidad de suspender es %.2f %%\n", suspenso * 100);	\
  } while (0)

#endif // OPOSIM_H_INCLUDED
