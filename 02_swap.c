/*@ requires \valid(a);
    requires \valid(b);

    assigns *a;
    assigns *b;

    ensures *a == \old(*b);
    ensures *b == \old(*a);
 */
void swap(int *a, int *b)
{
   int tmp = *b;
   *b = *a;
   *a = tmp;
}
