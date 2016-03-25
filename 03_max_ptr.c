/*@ requires \valid(a);
    requires \valid(b);

    assigns *a;
    assigns *b;

    ensures *a == \old(*b);
    ensures *b == \old(*a);
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
      ensures *a == \old(*b);
      ensures *b == \old(*a);
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
