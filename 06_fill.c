/*@ requires n >= 0;
    requires \valid(p + (0 .. n-1));

    terminates \true;
    assigns p[0 .. n-1];

    ensures \forall integer i; 0 <= i < n ==> p[i] == val;
 */
void fill(int *p, int n, int val)
{
   /*@ loop invariant 0 <= i <= n;
       loop invariant \forall integer k; 0 <= k < i ==> p[k] == val;
       loop variant n - i;
    */
   for(int i = 0; i < n; ++i) {
      p[i] = val;
   }
}
