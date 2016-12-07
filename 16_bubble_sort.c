

#pragma JessieTerminationPolicy(user)


/*@
  predicate sorted{Here}(int* a, integer start_index, integer end_index) =
    \forall integer k1, k2;
    start_index <= k1 <= k2 <= end_index ==> a[k1] <= a[k2];
*/

/*@ 
  predicate swapped{L1,L2}(int* a, integer i, integer j) = 
  \at(a[i],L1) == \at(a[j],L2) && 
  \at(a[j],L1) == \at(a[i],L2) && 
  \forall integer k; k != i && k != j  
     ==> \at(a[k],L1) == \at(a[k],L2); 
  */ 

/*@ 
  inductive IPermut{L1,L2}(int* a, integer index_start, integer end_start) 
  { 
  case Permut_refl{L}:  
  \forall int* a, integer index_start, end_start;
  IPermut{L,L}(a, index_start, end_start); 
  
  case Permut_sym{L1,L2}:  
  \forall int* a, integer index_start, end_start;  
  IPermut{L1,L2}(a, index_start, end_start) ==> 
  IPermut{L2,L1}(a, index_start, end_start); 
  
  case Permut_trans{L1,L2,L3}:  
  \forall int* a, integer index_start, end_start;  
  IPermut{L1,L2}(a, index_start, end_start) && 
  IPermut{L2,L3}(a, index_start, end_start) ==>  
  IPermut{L1,L3}(a, index_start, end_start); 

  case Permut_swap{L1,L2}:  
  \forall int* a, integer index_start, end_start, i, j;  
  index_start <= i <= end_start && index_start <= j <= end_start &&
  swapped{L1,L2}(a, i, j) ==>  
  IPermut{L1,L2}(a, index_start, end_start); 
  } 
  */ 

 
/*@ 
  requires \valid(t+i) && \valid(t+j); 
  //assigns t[i],t[j]; 
  ensures \forall integer k; 
	0 <= k < n && k != i && k != j ==> t[k] == \old(t[k]);
  ensures swapped{Old,Here}(t,i,j); 
  */ 
void sort_swap3(int t[], int i, int j, int n) { 
  int tmp = t[i]; 
  t[i] = t[j]; 
  t[j] = tmp; 
} 
 
/*@
  requires 0 < length;
  requires \valid(a+(0..length-1));
  //assigns a[0..length-1];
  behavior sorted: 
		ensures sorted(a, 0, length-1);
  behavior permutation: 
		ensures IPermut{Old,Here}(a, 0, length-1);
*/
void bubble_sort(int* a, int length) 
{
	int up = 1;
	int down;
	int fixed_up = up;

	/*@
   // loop assigns a[0..up-1];
		for sorted:  
			loop invariant fixed_up == up;
			loop invariant 0 < up <= length; 
			loop invariant sorted(a, 0, up-1);		
			loop invariant \forall integer k; 
				up < k < length ==> a[k] == \at(a[k], Pre);
		for permutation:
			loop invariant IPermut{Pre,Here}(a, 0, length-1);
	*/
	for (; up < length; up++, fixed_up = up)   
	{   
		//@ for sorted: assert sorted(a, 0, up-1);				
    //@ for permutation: assert IPermut{Pre,Here}(a, 0, length-1);
		fixed_up = up;
		down=up; 
		//@ for sorted: assert sorted(a, down, up);
    //@ assert down < length;
		/*@
     //  loop assigns a[down+1..up];
    
			for sorted:
				loop invariant fixed_up == up;
        loop invariant 0 <= down < length;
				loop invariant 0 <= down <= up < length;
				loop invariant sorted(a, 0, down-1);
				loop invariant sorted(a, down, up);
				loop invariant \forall integer k;
					up < k < length ==> a[k] == \at(a[k], Pre);
				loop invariant  0 < down < up ==> a[down-1] <= a[down+1];
			for permutation:
				loop invariant IPermut{Pre,Here}(a, 0, length-1);
		*/    
		while (0 < down && a[down] < a[down-1] )
		{    
      //@ for permutation: assert IPermut{Pre,Here}(a, 0, length-1);
		  //@ for sorted: assert sorted(a, 0, down-1);			 
		  //@ for sorted: assert sorted(a, down, up);			
		  //@ for sorted: assert a[down] < a[down-1];								
		  
		  sort_swap3(a,down,down-1, length); 
		  //@ for permutation: assert IPermut{Pre,Here}(a, 0, length-1);
		  //@ for sorted: assert a[down-1] <= a[down]; 
			//@ for sorted: assert sorted(a, 0, down-2);			
			//@ for sorted: assert sorted(a, down, up);						
			// ==>			
			
			//@ for sorted: assert sorted(a, down-1, up);	
			down = down-1;                 
			//@ for sorted: assert sorted(a, 0, down-1);				
			//@ for sorted: assert sorted(a, down, up);			
			 //@ for permutation: assert IPermut{Pre,Here}(a, 0, length-1);
		}
		//@ for sorted: assert sorted(a, 0, up);
     //@ for permutation: assert IPermut{Pre,Here}(a, 0, length-1);
	}
   //@ for permutation: assert IPermut{Pre,Here}(a, 0, length-1);
} 
