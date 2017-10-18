#include <stdio.h>
#include <stdlib.h>

#include "all.h"

typedef struct litteral {
  int x;
  int i;
  struct litteral *next;
} *litteral;

typedef struct clause {
  litteral first;
  struct clause *next;
} *clause;

litteral new_litteral(int x, int i){
  litteral l = malloc(sizeof(struct litteral));
  l->x = x;
  l->i = i;
  l->next = NULL;
  return l;
}

clause new_clause(){
  clause c = malloc(sizeof(struct clause));
  c->first = NULL;
  c->next = NULL;
  return c;
}

clause translate(int n, int k){
  clause sat1, sat2, c1, c2, c3;
  litteral l1, l2, l3, l4, l5;
  for (int u = 1; u <= n; u++){

    //Pour chaque sommet v ∈ V, il y a un unique entier h t.q. xv,h est vrai
    if(u==1){
      c1 = new_clause();
      sat1 = c1;
    } else {
      c1->next = new_clause();
      c1 = c1->next;
    }
    for(int i = 0; i <= k; i++){
      if(i==0) {
	l1 = new_litteral(u, i);
	c1->first = l1;
      } else {
	l1->next = new_litteral(u, i);
	l1 = l1->next;
      }
      for(int j = i + 1; j <= k; j++){
	c1->next = new_clause();
	c1 = c1->next;
	l2 = new_litteral(-u, i);
      l2->next = new_litteral(-u, j);
	c1->first = l2;
      }
    }

    //Il y a un unique sommet v t.q. d(v) = 0
    if(u == 1){
      c2 = new_clause();
      sat2 = c2;
      l3 = new_litteral(u, 0);
      c2->first = l3;
    } else {
      l3->next = new_litteral(u, 0);
      l3 = l3->next;
    }
    for(int v = u + 1; v <= n; v++){
      c2->next = new_clause();
      c2 = c2->next;
      l4 = new_litteral(-u, 0);
      l4->next = new_litteral(-v, 0);
      c2->first = l4;
    }

    //Il y a au moins un sommet v t.q. d(v) = k
    if(u == 1){
      c3 = new_clause();
      l5 = new_litteral(u, k);
      c3->first = l5;
    } else {
      l5->next = new_litteral(u, k);
      l5 = l5->next;
    }
    
  }
  c1->next = sat2;
  c2->next = c3;
  return sat1;
}

void afficher_sat(clause sat){
  while(sat != NULL){
    litteral l = sat->first;
    while(l != NULL){
      printf("%d,%d ", l->x, l->i);
      l = l->next;
    }
    printf("\n");
    sat = sat->next;
  }
}

void free_sat(clause sat){
  litteral tmp;
  clause c;
  while(sat != NULL){
    litteral l = sat->first;
    while(l != NULL){
      tmp = l;
      l = l->next;
      free(tmp);
    }
    c = sat;
    sat = sat->next;
    free(c);
  }
}

int main(int argc, char* argv[]){
  if(argc != 2){
    printf("./transale k\n");
    return 0;
  }
  //FILE *f = fopen("formule_sat", "w+");

  //int n = orderG();
  //int m = sizeG();
  int n = 5;
  int k = atoi(argv[1]);

  clause sat = translate(n, k);
  afficher_sat(sat);
  free_sat(sat);
  
  //fclose(f);
  return 1;
}
