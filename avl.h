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
t_node *rot_left(t_node *node);
t_node *rot_right(t_node *node);
t_node *insert_node(t_node *root, int key);
t_node *remove_node(t_node *node, int key);
void print_avl(t_node *node);
