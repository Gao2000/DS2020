#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

struct chain{
  int n; //highest degree
  double *an; //coffient of polynomial
};

void creat_chain(struct chain * c){
  int i, n;
  double ai;
  
  printf("please enter the highest degree of polynomial:");
  scanf("%d", &n);
  (*c).n = n;
  (*c).an = (double *)calloc(n+1, sizeof(double));

  for(int i = n; i >= 0; i--){
    scanf("%lf", &ai);
    (*c).an[i] = ai;
  }
}

void show(struct chain c){
  int i = c.n;
  printf("\n");
  while(i >= 0){
    if((i != c.n) && (c.an[i] >= 0))
      printf("+");
    switch(i)
    {
      case 1:
        printf("%.2lfX", c.an[i]);
        break;
      case 0:
        printf("%.2lf", c.an[i]);
        break;
      default:
        printf("%.2lfX^%d", c.an[i], i);
        break;
    }
    i--;
  }
  printf("\n");
}

void check_changes(struct chain *r){
  int i = (*r).n;
  while((fabs((*r).an[i]) <= 1e-5) && (i >= 0))
    i--;
  (*r).n = i;
}

bool check_zero(struct chain r){
  for(int i = 0; i <= r.n; i++)
    if(fabs(r.an[i]) >= 1e-6)
      return false;
  return true;
}

void do_div(struct chain ch1, struct chain ch2) //Eculidean algorithim ch1 = q * ch2 + r
{
  int i = 0, j;
  double tmp;
  struct chain q, r;
  if(check_zero(ch2)){
    printf("wrong ch2 is zero\n");
    exit(0);
  }
  
  if(ch1.an[ch1.n] < ch2.an[ch2.n])
    for(int k = 0; k <= ch1.n; k++)
      ch1.an[k] *= ch2.an[ch2.n];

  printf("////////////////////////////\nch1:");
  show(ch1);
  printf("ch2:");
  show(ch2);
  printf("////////////////////////////\n");

  q.n = ch1.n - ch2.n;
  r.n = ch1.n - 1;
  q.an = (double*)calloc(q.n+1, sizeof(double));
  r.an = (double*)calloc(r.n+1, sizeof(double));
  while(i <= q.n){
    r.n = ch1.n - 1;
    q.an[q.n - i] = ch1.an[ch1.n]/ch2.an[ch2.n];
    tmp = q.an[q.n - i];

    for(j = r.n; j >= 0; j--){
      if(j >= q.n-i)
        r.an[j] = ch1.an[j] - tmp*ch2.an[j-q.n+i]; //higher degree minius each other
      else
        r.an[j] = ch1.an[j]; //lower term stay steady
    }
    if(check_zero(r)) break;
    ch1 = r;
    i++;
  }
  printf("===========================\n");
  printf("q(x):");
  show(q);
  printf("r(x):");
  show(r);
  printf("===========================\n");

  check_changes(&r);

  if(r.n == -1){
    show(ch2);
    free(r.an);
  }
  else
    do_div(ch2, r);
}

void main(){
  struct chain ch1, ch2;
  creat_chain(&ch1);
  show(ch1);
  printf("------------------------------------------------------\n");
  creat_chain(&ch2);
  show(ch2);

  do_div(ch1,ch2);

  free(ch1.an);
  free(ch2.an);
}
