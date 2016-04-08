struct node
{
   struct node *right;
   struct node *left;
   unsigned long value;
};

struct root { struct node *node; };

/*@
  @ //Calc num of nodes
  @ axiomatic btree_calc_size {
  @    logic integer calc_size{L}(struct node * node) =
  @       (node == \null) ? 0 :
  @          calc_size(node->right) + calc_size(node->left) + 1;
  @
  @    //axiom calc_size_nonnegative:
  @    //   \forall struct node * node;
  @    //      calc_size(node) >= 0;
  @ }
  @ */

/*@ inductive exists_in_tree{L}(struct node *node, integer v) {
  @    case exists1{L}:
  @       \forall struct node *node, integer v;
  @       \valid(node) && node->value == v ==>
  @       exists_in_tree(node, v);
  @    case exists2{L}:
  @       \forall struct node *node, integer v;
  @       \valid(node) && exists_in_tree(node->left, v) ==>
  @       exists_in_tree(node, v);
  @    case exists3{L}:
  @       \forall struct node *node, integer v;
  @       \valid(node) && exists_in_tree(node->right, v) ==>
  @       exists_in_tree(node, v);
  @ }
  @*/

/*@ inductive correct_btree{L}(struct node * node) {
  @    case nil{L}:
  @       correct_btree(\null);
  @    case next{L}:
  @       \forall struct node *node;
  @          \valid(node) &&
  @          correct_btree(node->left) &&
  @          correct_btree(node->right) &&
  @          (\forall integer v; exists_in_tree(node->left, v) ==> v < node->value) &&
  @          (\forall integer v; exists_in_tree(node->right, v) ==> v > node->value) ==>
  @             correct_btree(node);
  @ }
  @*/

/*@ inductive size_correct{L}(struct node *node) {
  @   case nil{L}:
  @     size_correct(\null);
  @   case ind{L}:
  @     \forall struct node * node; \valid(node) ==>
  @       calc_size(node->left) >= 0 && calc_size(node->right) >= 0 ==>
  @       size_correct(node->left) && size_correct(node->right) ==>
  @       size_correct(node);
  @ }
  @ */


/*@ requires \valid(root); // pointer is non-null
  @ requires correct_btree(root->node); // tree has proper structure
  @ requires size_correct(root->node);
  @ ensures \result != \null <==> exists_in_tree(root->node, value);
  @ ensures \result != \null ==>
  @            (
  @               \valid(\result) &&
  @               \result->value == value
  @            );
  @*/
struct node* search_node(struct root* root, unsigned long value)
{
	struct node* n = root->node;

	/*@ loop invariant exists_in_tree(root->node, value) <==> exists_in_tree(n, value);
	  @ loop invariant correct_btree(n);
     @ loop invariant size_correct(n);
     @ loop invariant calc_size(n) >= 0;
	  @ loop variant (calc_size(n));
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
