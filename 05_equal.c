#include <stdbool.h>

/*@ requires n >= 0;
    requires \valid(a + (0 .. n-1));
    requires \valid(b + (0 .. n-1));

    assigns \nothing;

    behavior eq:
      assumes \forall integer i; 0 <= i < n ==> a[i] == b[i];
      ensures \result;
    behavior neq:
      assumes \exists integer i; 0 <= i < n && a[i] != b[i];
      ensures !\result;
    complete behaviors;
    disjoint behaviors;
 */
bool equal(int *a, int n, int *b)
{
   /*@ loop invariant 0 <= i <= n;
       loop invariant \forall integer k; 0 <= k < i ==> a[k] == b[k];
       loop variant n - i;
    */
   for(int i = 0; i < n; ++i) {
      if (a[i] != b[i]) {
         return false;
      }
   }
   return true;
}
