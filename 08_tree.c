#ifndef NULL
# define NULL ((void *)0)
#endif

struct node
{
	struct node *right;
	struct node *left;
	struct node *parent;
	unsigned long   value;
};


struct root
{
	struct node *node;
};

struct node* search_node(struct root* root, unsigned long value);

#define parent(r)   ((r)->parent)

/*@ //Find value in tree.
  @ axiomatic rbtree_find_value {
  @   logic struct node * find_in_tree{L}(struct node * node, integer value);
  @
  @   axiom present_in_given_node:
  @      \forall struct node * node, integer value;
  @         \valid(node) && node->value == value 
  @           ==> find_in_tree(node, value) == node;
  @
  @   axiom null_not_found:
  @      \forall integer value;
  @        find_in_tree(\null, value) == \null;
  @ 
  @   axiom left_child:
  @      \forall struct node * node, integer value;
  @         \valid(node) && node->value > value
  @         ==> find_in_tree(node, value) == find_in_tree(node->left, value);
  @
  @   axiom right_child:
  @      \forall struct node * node, integer value;
  @         \valid(node) && node->value < value
  @         ==> find_in_tree(node, value) == find_in_tree(node->right, value);
  @ }
  @
  @ //Calc num of nodes
  @ axiomatic rbtree_calc_size {
  @    logic integer calc_size{L}(struct node * node);
  @    axiom null_size:
  @       calc_size(\null) == 0;
  @    axiom not_null_size:
  @       \forall struct node * node;
  @          \valid(node) ==> (calc_size(node) == (1 + calc_size(node->left) + calc_size(node->right)));
  @
  @    axiom calc_size_child:
  @       \forall struct node * node;
  @          \valid(node) ==> ((calc_size(node) > calc_size(node->left)) && calc_size(node) > calc_size(node->right));
  @
  @    axiom calc_size_nonnegative:
  @       \forall struct node * node;
  @          \valid(node) ==> (calc_size(node) >= 0);
  @ }
  @ */

/* Tools workaround */
/*@
  @ lemma valid_tools_workaround_nonull:
  @   \forall struct node *node;
  @      ((node != \null) ==> (\valid(node)));
  @
  @ lemma valid_tools_workaround_single_standalone:
  @   \forall struct node *node;
  @      (\valid(node) && node->parent != node) ==>
  @        (node->parent->parent != node->parent);
  @ */

/* Type invariants. */
/*@
  @ lemma type_invariant_child_nodes:
  @   \forall struct node * node;
  @     \valid(node) && \valid(node->parent) ==>
  @       (node == node->parent->left || node == node->parent->right);
  @
  @ // If given node has value less then parent node value, then 
  @ // it's left child for it's parent.
  @ lemma type_invariant_node_values_parent_left:
  @   \forall struct node * node;
  @    (\valid(node) && \valid(parent(node))
  @     ==>
  @     ((parent(node)->value > node->value) <==>
  @      (parent(node)->left == node)));
  @
  @ // If given node has value greater then parent node value, then 
  @ // it's right child for it's parent.
  @ lemma type_invariant_node_values_parent_right:
  @   \forall struct node * node;
  @    (\valid(node) && \valid(parent(node)) 
  @     ==>
  @     ((parent(node)->value < node->value) <==>
  @      (parent(node)->right == node)));
  @
  @ // Childler of given node have this node as parent.
  @ lemma type_invariant_parent_child_left:
  @  \forall struct node * node;
  @   \valid(node) ==>
  @    (\valid(node->left) ==> parent(node->left) == node);
  @
  @ lemma type_invariant_parent_child_right:
  @  \forall struct node * node;
  @   \valid(node) ==>
  @    (\valid(node->right) ==> parent(node->right) == node);
  @
  @*/


/*@ // requires all type_invariants for root are true
    requires \valid(root); // pointer is non-null
    ensures \result == find_in_tree(root->node, value);
    ensures \result != \null ==>
               (
                  \valid(\result) &&
                  \result->value == value
               );
 */
struct node* search_node(struct root* root, unsigned long value)
{
	struct node* n = root->node;

	/*@ loop invariant find_in_tree(root->node, value) == find_in_tree(n, value);
	    loop invariant find_in_tree(root->node, value) != \null ==> \valid(n);
	    loop variant (calc_size(n));
	*/
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

