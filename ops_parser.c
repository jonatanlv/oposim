#include <argp.h>
#include <stdlib.h>

#include "oposim.h"

const char *argp_program_version = "oposim 1.0";

const char *argp_program_bug_address = "<jonatanlv@gmail.com>";

static char doc[] = "Simulador de oposiciones -- Pequeño programa para simular el resultado de unas oposiciones";

static struct argp_option options[] = {
  {"temas", 't', "TEMAS", 0, "Número de temas en la oposición. Por defecto 72."},
  {"bolas", 'b', "BOLAS", 0, "Número de bolas extraídas. Por defecto 4."},
  {"estudiados", 'e', "ESTUDIADOS", 0, "Número de temas estudiados. Por defecto 50."},
  {"min", 'm', "MIN", 0, "Mínimo número de temas que es necesario saber para aprobar. Por defecto 1."},
  {"reps", 'r', "REPS", 0, "Número de repeticiones del experimento. Por defecto 1e6."},
  {"rng", 'g', "RNG", 0, "RNG usado. Por defecto gsl_rng_mrg. Los valores que puede tomar esta variable son: m MT19937, t Tausworthe, g lagged-fibonacci, x RANLUX 2"},
  {0}
};

static error_t parse_opt (int key, char *arg, struct argp_state *state)
{

  struct args_s *arguments = state->input;

  switch(key) {
  case 't':
    arguments->temas = arg ? atoi(arg) : TEMAS_D;
    break;
  case 'b':
    arguments->bolas = arg ? atoi(arg) : BOLAS_D;
    break;
  case 'e':
    arguments->estudiados = arg ? atoi(arg) : ESTUDIADOS_D;
    break;
  case 'm':
    arguments->min = arg ? atoi(arg) : MIN_D;
    break;
  case 'r':
    arguments->reps = arg ? (int)atof(arg) : REPS_D;
    break;
  case 'g':
    arguments->rng = arg ? arg[0] : RNG_D;
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = {options, parse_opt, 0, doc};

error_t ops_parser(int argc, char **argv, args_s *arguments) {

  return argp_parse (&argp, argc, argv, 0, 0, arguments);

}
