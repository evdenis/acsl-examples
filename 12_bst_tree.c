#ifndef NULL
# define NULL ((void *)0)
#endif


struct rbnode
{
   struct rbnode *right;
   struct rbnode *left;
   unsigned long value;
};

struct root { struct rbnode *rbnode; };

/*@
  @ //Calc num of rbnodes
  @ axiomatic btree_calc_size {
  @    logic integer rbcalc_size{L}(struct rbnode * rbnode) =
  @       (rbnode == \null) ? 0 :
  @          rbcalc_size(rbnode->right) + rbcalc_size(rbnode->left) + 1;
  @
  @    //axiom rbcalc_size_nonnegative:
  @    //   \forall struct rbnode * rbnode;
  @    //      rbcalc_size(rbnode) >= 0;
  @ }
  @ */

/*@ inductive exists_in_tree{L}(struct rbnode *rbnode, integer v) {
  @    case exists1{L}:
  @       \forall struct rbnode *rbnode, integer v;
  @       \valid(rbnode) && rbnode->value == v ==>
  @       exists_in_tree(rbnode, v);
  @    case exists2{L}:
  @       \forall struct rbnode *rbnode, integer v;
  @       \valid(rbnode) && exists_in_tree(rbnode->left, v) ==>
  @       exists_in_tree(rbnode, v);
  @    case exists3{L}:
  @       \forall struct rbnode *rbnode, integer v;
  @       \valid(rbnode) && exists_in_tree(rbnode->right, v) ==>
  @       exists_in_tree(rbnode, v);
  @ }
  @*/

/*@ inductive correct_btree{L}(struct rbnode * rbnode) {
  @    case nil{L}:
  @       correct_btree(\null);
  @    case next{L}:
  @       \forall struct rbnode *rbnode;
  @          \valid(rbnode) &&
  @          correct_btree(rbnode->left) &&
  @          correct_btree(rbnode->right) &&
  @          (\forall integer v; exists_in_tree(rbnode->left, v) ==> v < rbnode->value) &&
  @          (\forall integer v; exists_in_tree(rbnode->right, v) ==> v > rbnode->value) ==>
  @             correct_btree(rbnode);
  @ }
  @*/

/*@ inductive size_correct{L}(struct rbnode *rbnode) {
  @   case nil{L}:
  @     size_correct(\null);
  @   case ind{L}:
  @     \forall struct rbnode * rbnode; \valid(rbnode) ==>
  @       rbcalc_size(rbnode->left) >= 0 && rbcalc_size(rbnode->right) >= 0 ==>
  @       size_correct(rbnode->left) && size_correct(rbnode->right) ==>
  @       size_correct(rbnode);
  @ }
  @ */


/*@ requires \valid(root); // pointer is non-null
  @ requires correct_btree(root->rbnode); // tree has proper structure
  @ requires size_correct(root->rbnode);
  @ ensures \result != \null <==> exists_in_tree(root->rbnode, value);
  @ ensures \result != \null ==>
  @            (
  @               \valid(\result) &&
  @               \result->value == value
  @            );
  @*/
struct rbnode* search_rbnode(struct root* root, unsigned long value)
{
	struct rbnode* n = root->rbnode;

	/*@ loop invariant exists_in_tree(root->rbnode, value) <==> exists_in_tree(n, value);
	  @ loop invariant correct_btree(n);
     @ loop invariant size_correct(n);
     @ loop invariant rbcalc_size(n) >= 0;
	  @ loop variant (rbcalc_size(n));
	  @*/
	while (n)
	{
		if (value < n->value)
			n = n->left;
		else if (value > n->value)
			n = n->right;
		else
			return n;
	}
	return NULL;
}
