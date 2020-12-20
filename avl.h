// Luan Machado Bernardt | GRR20190363

#ifndef __AVL__
#define __AVL___

typedef struct t_node {

	struct t_node *parent;
	struct t_node *left;
	struct t_node *right;
	int height;
	int balance;
	int key;
	int level;

} t_node;

t_node *new_node(int key);
int node_height(t_node *root);
int node_balance(t_node *root);
t_node *update_node(t_node *node);
t_node *rot_left(t_node *node);
t_node *rot_right(t_node *node);
t_node *insert_node(t_node *root, int key);
t_node *remove_node(t_node *node, int key);
int node_level(t_node *node);
void in_order(t_node *node);

#endif
