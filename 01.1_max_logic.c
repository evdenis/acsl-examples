/*@ logic integer max(integer a, integer b) =
          a > b ? a : b;
 */
/*@ assigns \nothing; 
    ensures \result >= a;
    ensures \result >= b;
    ensures \result == a || \result == b;
    ensures \result == max(a, b);
 */
int max(int a, int b)
{
   return a > b ? a : b;
}
