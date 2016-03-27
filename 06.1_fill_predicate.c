/*@ predicate is_equal_to_val(int *a, int n, int val) =
       \forall integer i; 0 <= i < n ==> a[i] == val;
 */

/*@ requires n >= 0;
    requires \valid(p + (0 .. n-1));

    terminates \true;
    assigns p[0 .. n-1];

    ensures is_equal_to_val(p, n, val);
 */
void fill(int *p, int n, int val)
{
   /*@ loop invariant 0 <= i <= n;
       loop invariant is_equal_to_val(p, i, val);
       loop variant n - i;
    */
   for(int i = 0; i < n; ++i) {
      p[i] = val;
   }
}
