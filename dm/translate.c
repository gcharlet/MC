#include <stdio.h>
#include <stdlib.h>

#include "all.h"

typedef struct litteral {
  int x;
  int i;
  int etat;
  struct litteral *next;
} *litteral;

typedef struct clause {
  litteral first;
  struct clause *next;
} *clause;

litteral new_litteral(int x, int i, int etat){
  litteral l = malloc(sizeof(struct litteral));
  l->x = x;
  l->i = i;
  l->etat = etat;
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
  clause sat1, sat2, sat4 = NULL, c1, c2, c3, c4;
  litteral l1, l2, l3, l4, l5, l6;
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
	l1 = new_litteral(u, i, 1);
	c1->first = l1;
      } else {
	l1->next = new_litteral(u, i, 1);
	l1 = l1->next;
      }
      for(int j = i + 1; j <= k; j++){
	c1->next = new_clause();
	c1 = c1->next;
	l2 = new_litteral(u, i, -1);
	l2->next = new_litteral(u, j, -1);
	c1->first = l2;
      }
    }

    //Il y a un unique sommet v t.q. d(v) = 0
    if(u == 1){
      c2 = new_clause();
      sat2 = c2;
      l3 = new_litteral(u, 0, 1);
      c2->first = l3;
    } else {
      l3->next = new_litteral(u, 0, 1);
      l3 = l3->next;
    }
    for(int v = u + 1; v <= n; v++){
      c2->next = new_clause();
      c2 = c2->next;
      l4 = new_litteral(u, 0, -1);
      l4->next = new_litteral(v, 0, -1);
      c2->first = l4;
    }

    //Il y a au moins un sommet v t.q. d(v) = k
    if(u == 1){
      c3 = new_clause();
      l5 = new_litteral(u, k, 1);
      c3->first = l5;
    } else {
      l5->next = new_litteral(u, k, 1);
      l5 = l5->next;
    }

    //
    for(int i = 1; i <= k; i++){
      if(sat4 == NULL){
	c4 = new_clause();
	sat4 = c4;
      }else{
	c4->next = new_clause();
	c4 = c4->next;
      }
      l6 = new_litteral(u, i, -1);
      c4->first = l6;
      for(int v = 1; v <= n; v++){
	if(v != u && are_adjacent(u-1, v-1)){
	  l6->next = new_litteral(v, i-1, 1);
	  l6 = l6->next;
	}
      }
    }
    
  }
  c1->next = sat2;
  c2->next = c3;
  c3->next = sat4;
  return sat1;
}

void afficher_sat(clause sat, int n){
  printf("litteral : {v{V}, i{0:k-1}, etat(1 ou -1)}\n");
  while(sat != NULL){
    litteral l = sat->first;
    while(l != NULL){
      printf("{%d, %d, %d} ", l->x, l->i, l->etat);
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

void create_fichier(clause sat, int n, int k){
  FILE *f = fopen("fichier_sat", "w+");
  fprintf(f, "p cnf %d %d\n", n+n*k, n+n*(k*(k+1)/2)+n*(n-1)/2+n*k+2);
  while(sat != NULL){
    litteral l = sat->first;
    while(l != NULL){
      fprintf(f, "%d ", (l->x + n * l->i) * l->etat);
      l = l->next;
    }
    fprintf(f, "0\n");
    sat = sat->next;
  }
  fclose(f);
}

int main(int argc, char* argv[]){
  if(argc != 2){
    printf("./transale k\n");
    return 0;
  }

  int n = orderG();
  int k = atoi(argv[1]);

  clause sat = translate(n, k);
  //afficher_sat(sat, n);
  create_fichier(sat, n, k);
  free_sat(sat);
  
  return 1;
}
