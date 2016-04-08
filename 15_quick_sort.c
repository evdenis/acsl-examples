#pragma JessieIntegerModel(math)

#include "sorting.h"

/*@ requires \valid(t+i) && \valid(t+j);
  @ assigns t[i],t[j];
  @ ensures Swap{Old,Here}(t,i,j);
  @*/
void swap(int t[], int i, int j) {
  int tmp = t[i];
  t[i] = t[j];
  t[j] = tmp;
}

// quick_rec sorts t[l..r]
/*@ requires \valid_range(t,l,r);
  @ decreases r-l;
  @ assigns t[l..r];
  @ ensures Sorted(t,l,r+1);
  @ ensures Permut{Old,Here}(t,l,r);
  @*/
void quick_rec(int t[], int l, int r) {
  int v,m,i;
  if (l >= r) return;
  v = t[l];
  m = l; 
  /*@ loop invariant 
    @   \forall integer j; l < j <= m ==> t[j] < v;
    @ loop invariant
    @   \forall integer j; m < j <  i ==> t[j] >= v;
    @ loop invariant  
    @   Permut{Pre,Here}(t,l,r);
    @ loop invariant t[l] == v && l <= m < i <= r+1;
    @ loop variant r-i;
    @*/
  for (i = l + 1; i <= r; i++) {
    if (t[i] < v) {
    L1:
      swap(t,i,++m);
      //@ assert Permut{L1,Here}(t,l,r);
    }
  }
  //@ assert l <= m <= r;
 L: swap(t,l,m);
  //@ assert Permut{L,Here}(t,l,r);
  quick_rec(t,l,m-1);
  quick_rec(t,m+1,r);
}

/*@ requires \valid_range(t,0,n-1);
  @ ensures Sorted(t,0,n);
  @ ensures Permut{Old,Here}(t,0,n-1);
  @*/
void quick_sort(int t[], int n) {
  quick_rec(t,0,n-1);
}

