/***** var.c ****************************************************************
 * Description: Compute mean and variance
 * Author: Bernhard Haubold
 * Email: haubold@evolbio.mpg.de
 * License: GNU General Public License, https://www.gnu.org/licenses/gpl.html
 * Date: Fri Feb 15 09:24:24 2019
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "interface.h"
#include "eprintf.h"
#include "tab.h"

void printRes(long n, double m, double v) {
  printf("#n\tmean\tvar\n");
  printf("%ld\t%g\t%g\n", n, m, v);
}

void onePass(FILE *fp) {
  char *line;
  double x, sx = 0., sxx = 0., v, m;
  long n = 0;

  while((line = tabGetLine(fp)) != NULL) {
    if(line[0] == '#' || isalpha(line[0])) /* skip lines not containing a number */
      continue;
    x = atof(line);
    sx += x;
    sxx += x * x;
    n++;
  }
  v = (sxx - sx * sx / n) / (n - 1);
  m = sx / n;
  printRes(n, m, v);
}

void twoPass(FILE *fp) {
  long n = 0;
  long i;
  long maxN = 1;
  double x, mean, sx, sxx, var, diff;
  double *arr = emalloc(maxN * sizeof(double));
  char *line;

  while((line = tabGetLine(fp)) != NULL) {
    if(line[0] == '#' || isalpha(line[0])) /* skip lines not containing a number */
      continue;
    x = atof(line);
    arr[n++] = x;
    if(n == maxN){
      maxN *= 2;
      arr = erealloc(arr, maxN * sizeof(double));
    }
  }
  arr = erealloc(arr, n * sizeof(double));
  mean = 0;
  for(i=0;i<n;i++)
    mean += arr[i];
  mean /= n;
  sx = sxx = 0.;
  for(i=0;i<n;i++){
    diff = arr[i] - mean;
    sx += diff;
    sxx += diff * diff;
  }
  var = (sxx-sx*sx/n)/(n-1);
  printRes(n, mean, var);
 free(arr);
}

int main(int argc, char *argv[]){
  FILE *fp;
  Args *args = getArgs(argc, argv);

  setprogname2(argv[0]);
  if(args->v)
    printSplash(args);
  if(args->h || args->err)
    printUsage();
  if(args->nf == 0) {
    fp = stdin;
    if(args->o)
      onePass(fp);
    else
      twoPass(fp);
  } else {
    for(int i = 0; i < args->nf; i++) {
      fp = efopen(args->fi[i], "r");
      if(args->o)
	onePass(fp);
      else
	twoPass(fp);
      fclose(fp);
    }
  }
  tabFree();
  freeArgs(args);
  free(progname());
  return 0;
}

