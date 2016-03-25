/*@ assigns \nothing; 
    ensures \result >= a;
    ensures \result >= b;
    ensures \result == a || \result == b;
 */
int max(int a, int b)
{
   return a > b ? a : b;
}
