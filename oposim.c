/** \file oposim.c
    \brief Simulador de oposiciones.

    Breve simulador de oposiciones. Sirve para calcular las probabilidades de aprobar unas oposiciones sabiendo cuántas bolas sacan, cuantos temas hay en la oposición y cuántos temas lleva estudiados el alumno.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "oposim.h"

/** \mainpage principal

<code><pre>
Usage: oposim [-?V] [-b BOLAS] [-e ESTUDIADOS] [-g RNG] [-m MIN] [-r REPS]
            [-t TEMAS] [--bolas=BOLAS] [--estudiados=ESTUDIADOS] [--rng=RNG]
            [--min=MIN] [--reps=REPS] [--temas=TEMAS] [--help] [--usage]
            [--version]

  -b, --bolas=BOLAS          Número de bolas extraídas. Por defecto 4.
  -e, --estudiados=ESTUDIADOS   Número de temas estudiados. Por defecto 50.
  -g, --rng=RNG              RNG usado. Por defecto gsl_rng_mrg. Los valores
                             que puede tomar esta variable son: m MT19937, t
                             Tausworthe, g lagged-fibonacci, x RANLUX 2
  -m, --min=MIN              Mínimo número de temas que es necesario saber
                             para aprobar. Por defecto 1.
  -r, --reps=REPS            Número de repeticiones del experimento. Por
                             defecto 1e6.
  -t, --temas=TEMAS          Número de temas en la oposición. Por defecto 72.
                            
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version
</pre></code>
 */

int main(int argc, char **argv)
{

  args_s args = {.temas = TEMAS_D,
		 .bolas = BOLAS_D,
		 .estudiados = ESTUDIADOS_D,
		 .min = MIN_D,
		 .reps = REPS_D,
		 .rng = RNG_D};

  ops_parser(argc, argv, &args);

  printf("temas: %i\nbolas: %i\nestudiados: %i\nmin: %i\nreps: %i\n",
	 args.temas, args.bolas, args.estudiados, args.min,
	 args.reps);

  random_init(args.rng);

  int *cuentas = experimento(args.temas, args.bolas,
			     args.estudiados, args.reps);
  
  double *probs = frecs(cuentas, args.bolas + 1);

  free(cuentas);

  Print_Probs(probs, args.bolas + 1, args.min);

  free(probs);

  random_free();

}
