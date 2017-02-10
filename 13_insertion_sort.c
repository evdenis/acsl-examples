#include "sorting.h"

/*@ requires \valid(t + (0..n-1));
    ensures Sorted(t, 0, n-1);
 */
void insert_sort(int t[], int n)
{
   int i,j;
   int mv;
   if (n <= 1) return;

   /*@ loop invariant 0 <= i <= n;
       loop invariant Sorted(t, 0, i);
       loop variant n - i;
    */
   for (i = 1; i < n; i++) {
      // assuming t[0..i-1] is sorted, insert t[i] at the right place
      mv = t[i]; 
      // look for the right index j to put t[i]
      /*@ loop invariant 0 <= j <= i;
          loop invariant j == i ==> Sorted(t, 0, i);
          loop invariant j < i ==> Sorted(t, 0, i+1);
          loop invariant \forall integer k; j <= k < i ==> t[k] > mv;
          loop variant j;
       */
      for (j = i; j > 0; j--) {
         if (t[j-1] <= mv) break;
         t[j] = t[j-1];
      }
      t[j] = mv;
   }
}


