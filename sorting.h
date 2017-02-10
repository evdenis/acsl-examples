#ifndef SPEC_SORTING_H
#define SPEC_SORTING_H

/*@ predicate Swap{L1,L2}(int *a, integer i, integer j) =
       \at(a[i],L1) == \at(a[j],L2) &&
       \at(a[j],L1) == \at(a[i],L2) &&
       \forall integer k; k != i && k != j
          ==> \at(a[k],L1) == \at(a[k],L2);
 */

/*@ inductive Permut{L1,L2}(int *a, integer l, integer h) {
    case Permut_refl{L}:
      \forall int *a, integer l, h; Permut{L,L}(a, l, h);
    case Permut_sym{L1,L2}:
      \forall int *a, integer l, h;
        Permut{L1,L2}(a, l, h) ==> Permut{L2,L1}(a, l, h);
    case Permut_trans{L1,L2,L3}:
      \forall int *a, integer l, h;
        Permut{L1,L2}(a, l, h) && Permut{L2,L3}(a, l, h) ==>
          Permut{L1,L3}(a, l, h);
    case Permut_swap{L1,L2}:
      \forall int *a, integer l, h, i, j;
         l <= i <= h && l <= j <= h && Swap{L1,L2}(a, i, j) ==>
       Permut{L1,L2}(a, l, h);
   }
 */

/*@ predicate Sorted{L}(int *a, integer l, integer h) =
       \forall integer i,j; l <= i <= j < h ==> a[i] <= a[j];
 */

/*@ requires \valid(t+i);
    requires \valid(t+j);
    assigns t[i],t[j];
    ensures Swap{Old,Here}(t,i,j);
 */
void sort_swap(int t[], int i, int j)
{
   int tmp = t[i];
   t[i] = t[j];
   t[j] = tmp;
}

#endif
