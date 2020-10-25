#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


//int version
struct chain{
  int n; //highest degree
  int *an; //coffient of polynomial
};

void creat_chain(struct chain * c){
  int i, n;
  int ai;
  
  printf("please enter the highest degree of polynomial:");
  scanf("%d", &n);
  (*c).n = n;
  (*c).an = (int *)calloc(n+1, sizeof(double));

  for(int i = n; i >= 0; i--){
    scanf("%d", &ai);
    (*c).an[i] = ai;
  }
}

void show(struct chain c){
  int i = c.n; //degree

  printf("\n");
  while(i >= 0){
    if((i != c.n) && (c.an[i] >= 0))
      printf("+");
    switch(i)
    {
      case 1:
        printf("%dX", c.an[i]);
        break;
      case 0:
        printf("%d", c.an[i]);
        break;
      default:
        printf("%dX^%d", c.an[i], i);
        break;
    }
    i--;
  }
  printf("\n");
}

void check_changes(struct chain *r){
  int i = (*r).n;
  while((abs((*r).an[i]) <= 0) && (i >= 0))
    i--;
  (*r).n = i;
}

bool check_zero(struct chain r){
  for(int i = 0; i <= r.n; i++)
    if(abs(r.an[i]) >= 0)
      return false;
  return true;
}

int gcd(int i, int j){
  int shift = 0;

  //GCD(0,j) == j, GCD(i,0) == i, GCD(0,0) == 0
  if(i == 0) return j;
  if(j == 0) return i;

  //Let shift := lg K, where K is the greatest power of 2 dividing both i and j.
  while(((i | j) & 1) == 0){
    shift++;
    i >>= 1;
    j >>= 1;
  }
  while((i & 1) == 0)
    i >>= 1;

  //From here on, i is always odd.
  do{
    //remove all factor of 2 in v-- they are not common
    //note: v is not zero, so while will terminate
    while((j & 1) == 0)
      j >>= 1;

    /*Now i and j are both odd. Swap if necssary so i <= j, then set j = j - i
     * (which is even). For bignums, the swapping is just pointer movement, and
     * the subtraction can be done in-place
     */
    if(i > j){
      int t = i; i = j; j = t; //Swap i and j
    }

    j -= i; //Here j >= i
  }while(j != 0);

  //restore common factors of 2
  return i << shift;
}

void simplest(struct chain *r){
  int n = (*r).n;
  int i = (*r).an[n];
  printf("%d\n", i);
  for(int j = n - 1; j >= 0; j--)
    if((*r).an[j] != 0){
      printf("%d\n", (*r).an[j]);
      i = gcd(abs(i), abs((*r).an[j]));
    }

  printf("GCD: %d\n", i);
  
  for(int j = n; j >= 0; j--)
    (*r).an[j] /= i;

  printf("ans:");
  show((*r));
  printf("\n\n");
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
  
  //if(ch1.an[ch1.n] < ch2.an[ch2.n])
  for(int k = 0; k <= ch1.n; k++) //keep ch1.n % ch2.n == 0 
    ch1.an[k] *= ch2.an[ch2.n];

  printf("////////////////////////////\nch1:");
  show(ch1);
  printf("ch2:");
  show(ch2);
  printf("////////////////////////////\n");

  q.n = ch1.n - ch2.n;
  r.n = ch1.n - 1;
  q.an = (int*)calloc(q.n+1, sizeof(int));
  r.an = (int*)calloc(r.n+1, sizeof(int));

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
  if(ch2.an[ch2.n] < 0)
    for(int j = ch2.n; j >= 0; j--)
      ch2.an[j] *= -1;

  if(r.n == -1){
    simplest(&ch2);
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
