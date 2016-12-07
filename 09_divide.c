/*@ axiomatic CountAxiomatic {
    logic integer Count{L}(int* a, int v, integer i, integer j) reads a[i..(j-1)];
   
    axiom Count0:
       \forall int *a, v, integer i,j;
          i >= j ==> Count(a, v, i, j) == 0;
   
    axiom Count1:
       \forall int *a, v, integer i, j, k;
          0 <= i <= j <= k ==> Count(a, v, i ,k) == Count(a, v, i, j) + Count(a, v, j, k);
   
    axiom Count2:
       \forall int *a, v, integer i;
          (a[i] != v ==> Count(a, v, i, i+1) == 0) &&
          (a[i] == v ==> Count(a, v, i, i+1) == 1);
   
    logic integer CountWithHole{L}(int* c, int v, integer i, integer h, integer j) =
       Count{L}(c, v, i, h) + Count{L}(c, v, h+1, j);
   
    logic integer CountWithoutHole{L}(int* c, int v, integer i, integer h, integer j) =
       Count{L}(c, v, i, h) + Count{L}(c, v, h, j);
    }
   
    lemma CountLemma:
       \forall int *a, v, integer i;
          0 <= i ==> Count(a, v, 0, i+1) ==
          Count(a, v, 0, i) + Count(a, v, i, i+1);
   
    predicate Permutation{A,B}(int* c, int n) =
       \forall int x; Count{A}(c, x, 0, n) == Count{B}(c, x, 0, n);
*/

/*@ axiomatic Swapping {
    predicate PRSwap{L1,L2}(int *a, integer size) =
       \exists int i, int j; (size > 0 && i >= 0 && j >= 0 && i != j && i < size && j < size) ==>
       (\at(a[i],L1) == \at(a[j],L2) &&  \at(a[j],L1) == \at(a[i],L2) &&
       (\forall integer k; k != i && k != j && 0 <= k < size ==> \at(a[k],L1) == \at(a[k],L2)));
  
    lemma SCA{L1, L2}:
       \forall int* a, int size; PRSwap{L1, L2}(a, size) ==> Permutation{L1, L2}(a, size);
  
    lemma CA{L1}:
       \forall int* a, int size; (size > 0 && \forall integer k; 0 <= k < size ==> \at(\valid(a+k), L1)) ==> Permutation{L1, L1}(a, size);
  }
*/

/*@ requires \valid(x) && \valid(y);
    requires x == y || x != y;
    assigns *x, *y;
    ensures *y == \old(*x);
    ensures *x == \old(*y);
 */
void swap(int *x, int *y)
{
	int s = *x;
	*x = *y;
	*y = s;
}

/*@ requires size > 0;
    requires \valid(a+(0..size-1));

    ensures \exists int i; \forall int j; ((0 <= j < i) ==> (a[j] <= b));
    ensures \exists int i; \forall int j; ((i < j < size) ==> (a[j] >= b));
    ensures Permutation{Old, Here}(a, size);
 */
void divide(int a[], int size, int b)
{
	int l = 0;
	int r = size - 1;
	/*@ loop invariant \forall int j; (0 <= j < l ==> a[j] <= b) && (r < j < size ==> a[j] >= b);
	    loop invariant r >= 0 && r < size && l >= 0 && l < size;
	    loop invariant \valid(a+(0..size-1));
	    loop invariant Permutation{Pre, Here}(a, size);
	    loop variant (r - l);
	 */
	while (l < r)
	{
		if (a[l] <= b) ++l;
		else if (a[r] >= b) --r;
		else
		{
			swap(&(a[l]), &(a[r]));
			++l; --r;
		}
	}
}


