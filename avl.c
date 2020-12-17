#include <stdio.h>
#include "avl.h"
#include <stdlib.h>

t_node *new_node(int key) {

	t_node *node = malloc(sizeof(t_node));

	node->key = key;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->height = 0;
	node->balance = 0;
	node->level = 0;
	return node;
}

int node_height(t_node *root) {

	int maxl, maxr;
	
	if (!root)
		return -1;

	if ((maxl = node_height(root->left)) > (maxr = node_height(root->right)))
	       	return (1 + maxl);
	else
		return (1 + maxr);
}

int node_balance(t_node *root) {

	if (!root)
		return 0;

	return (node_height(root->left) - node_height(root->right));

}


t_node *rot_left(t_node *node) {

	t_node *aux;

	aux = node->right;
	aux->parent = node->parent;
	node->parent = aux;
	
	node->right = aux->left;
	if (node->right)
		node->right->parent = node;
	
	aux->left = node;
	aux->height = node_height(aux);
	node->height = node_height(node);
	aux->balance = node_balance(aux);
	node->balance = node_balance(node);
	return aux;
}

t_node *rot_right(t_node *node) {

	t_node *aux;

	aux = node->left;
	aux->parent = node->parent;
	node->parent = aux;

	node->left = aux->right;
	if (node->left)
		node->left->parent = node;

	aux->right = node;
	aux->height = node_height(aux);
	node->height = node_height(node);
	aux->balance = node_balance(aux);
	node->balance = node_balance(node);
	return aux;
}

t_node *fix_balance(t_node *node) {

	if (node->balance < -1) {
		if (node->right->balance > 0)
			node->right = rot_right(node->right);
		node = rot_left(node);

	} 
	else if (node->balance > 1) {
		if (node->left->balance < 0)
		       node->left = rot_left(node->left);
		node = rot_right(node);	
	}
	
	return node;
}
	
t_node *insert_node(t_node *node, int key) {

	if (!node)
		return new_node(key);

	if (key < node->key) {
		node->left = insert_node(node->left,key);
		node->left->parent = node;
	} else if (key > node->key) { 
		node->right = insert_node(node->right,key);
		node->right->parent = node;
	} else
		return node;
	
	node->height = node_height(node);
	node->balance = node_balance(node);
	node = fix_balance(node);

	return node;
}

t_node *remove_node(t_node *node, int key) {

	t_node *aux;
	
	if (!node)
		return node;

	if (key < node->key)
		node->left = remove_node(node->left,key);
	else if (key > node->key)
		node->right = remove_node(node->right,key);
	else {
		if ((!node->left) || (!node->right)) { 
			if (node->right) {
				aux = node->right;
				node = aux;
				free(aux);
			}
			else if (node->left) {
				aux = node->left;
				node = aux;
				free(aux);
			} else {
				aux = node;
				node = NULL;
				free(aux);
			}
		} else {
			aux = node->left;
			while(aux->left)
				aux = aux->right;
			node->key = aux->key;
			node->left = remove_node(node->left,node->key);
		}

	}
	
	if(!node)
		return node;

	node->height = node_height(node);
	node->balance = node_balance(node);
	node = fix_balance(node);

	return node;
}

int node_level(t_node *node) {

	if (!node->parent)
		return 0;

	return (node->parent->level + 1);
}

void print_avl(t_node *node) {

	if (!node)
		return;
	
	node->level = node_level(node);
	print_avl(node->left);
	printf("%d,%d\n",node->key,node->level);		
	node->level = node_level(node);
	print_avl(node->right);
}
		

