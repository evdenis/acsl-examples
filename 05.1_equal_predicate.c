#include <stdbool.h>

/*@ predicate is_equal(int *a, int n, int *b) =
       \forall integer i; 0 <= i < n ==> a[i] == b[i];
 */

/*@ requires n >= 0;
    requires \valid(a + (0 .. n-1));
    requires \valid(b + (0 .. n-1));

    assigns \nothing;
    ensures is_equal(a, n, b) ? \result : !\result;
 */
bool equal(int *a, int n, int *b)
{
   /*@ loop invariant 0 <= i <= n;
       loop invariant is_equal(a, i, b);
       loop variant n - i;
    */
   for(int i = 0; i < n; ++i) {
      if (a[i] != b[i]) {
         return false;
      }
   }
   return true;
}
