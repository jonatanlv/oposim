/** \file oposim_fns.c 
    \brief Funciones auxiliares
*/

#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <time.h>
#include <stdlib.h>

#include "oposim.h"

static gsl_rng *r = NULL; /**< \a r es el generador de números aleatorios */

/** \fn void random_init(char opc)
\brief Inicializador del generador de números aleatorios.
\param opc a character.
 */
void random_init(char opc)
{

  if (!r) {
    switch(opc) {
    case 'm':
      r = gsl_rng_alloc(gsl_rng_mt19937);
      break;
    case 't':
      r = gsl_rng_alloc(gsl_rng_taus);
      break;
    case 'g':
      r = gsl_rng_alloc(gsl_rng_gfsr4);
      break;
    case 'x':
      r = gsl_rng_alloc(gsl_rng_ranlxs0);
      break;
    default:
      r = gsl_rng_alloc(gsl_rng_mrg);
    }
    printf("Usando RNG %s\n", gsl_rng_name(r));
    gsl_rng_set(r, time(NULL));
  }

}

/** \fn void random_free()
\brief Destructor del generador de números aleatorios
*/
void random_free()
{

  if (!r) {
    gsl_rng_free(r);
  }

}

/** \fn int s_experimento(int temas, int bolas, int estudiados)
\brief Realiza una simulación.
\param temas Número de temas en la oposición.
\param bolas Número de bolas que se extraen.
\param estudiados Número de temas estudiados.
\return Número temas estudiados que estarían entre los extraídos.
*/
int s_experimento(int temas, int bolas, int estudiados)
{

  //printf("bolas extraidas: ");
  int b_extraidas[bolas];
  int bola;

  for (int i = 0; i < bolas; i++) {
    do {
      bola = (int) gsl_rng_uniform_int(r, temas) + 1;
      for (int j = 0; j < i; j++) {
	if (b_extraidas[j] == bola) {
	  bola = 0;
	  break;
	}
      }
    } while (!bola);
    //printf("%d ", bola);
    b_extraidas[i] = bola;
  }

  int res = 0;
  for (int i = 0; i < bolas; i++) {
    if(b_extraidas[i] <= estudiados) res++;
  }

  //printf("\n");
  return res;

}

/** \fn int *experimento(int temas, int bolas, int estudiados, int reps)
\brief Realiza varias simulaciones y devuelve los resultados.
\param temas Número de temas en la oposición.
\param bolas Número de bolas que se extraen.
\param estudiados Número de temas estudiados.
\param reps Número de veces que se realizará el experimento.
\return Histograma con las veces que el número de temas estudiados estaba entre las bolas extraídas.
 */
int *experimento(int temas, int bolas, int estudiados, int reps)
{

  int *res = (int *)calloc(bolas + 1, sizeof(int));

  for (int i = 0; i < reps; i++)
    res[s_experimento(temas, bolas, estudiados)]++;

  return res;

}

/** \fn double *frecs(int *histograma, int l)
\brief Calcula las frecuencias relativas.
\param histograma array de frecuencias absolutas
\param l longitud del histograma
\return array con las frecuencias relativas
 */
double *frecs(int *histograma, int l)
{

  double suma = 0;
  for (int i = 0; i < l; i++)
    suma += histograma[i];

  double *res = (double *)calloc(l, sizeof(double));

  for (int i = 0; i < l; i++)
    res[i] = histograma[i] / suma;

  return res;

}
