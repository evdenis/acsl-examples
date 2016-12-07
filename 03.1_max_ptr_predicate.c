/*@ predicate pr_swapped{L1,L2}(int *a, int *b) =
       \at(*a,L1) == \at(*b,L2) &&
       \at(*b,L1) == \at(*a,L2);
 */

/*@ requires \valid(a);
    requires \valid(b);

    assigns *a;
    assigns *b;

    ensures pr_swapped{Here,Pre}(a,b);
 */
void swap(int *a, int *b);

/*@ requires \valid(a);
    requires \valid(b);

    assigns *a, *b;

    ensures *a <= *b;
    behavior ret:
      assumes *a <= *b;
      ensures *a == \old(*a);
      ensures *b == \old(*b);
    behavior swap:
      assumes *a > *b;
      ensures pr_swapped{Here,Pre}(a, b);
    complete behaviors;
    disjoint behaviors;
 */
void max_ptr(int *a, int *b)
{
   if (*a <= *b) {
      return;
   } else {
      swap(a, b);
   }
}
