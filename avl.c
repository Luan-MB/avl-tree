#include <stdio.h>
#include "avl.h"
#include <stdlib.h>

// Função que cria novo nodo do tipo t_node * com a chave "key"
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

// Função que calcula a altura do node "root"
int node_height(t_node *root) {

	int maxl, maxr;
	
	if (!root)
		return -1;
	// Calcula-se a altura para a direita e para a esquerda, retorna-se a maior
	if ((maxl = node_height(root->left)) > (maxr = node_height(root->right)))
	       	return (1 + maxl);
	else
		return (1 + maxr);
}

// Função que calcula fator de balanço do nodo "node"
int node_balance(t_node *root) {

	if (!root)
		return 0;

	return (node_height(root->left) - node_height(root->right));

}

t_node *refresh_node(t_node *node) {

	node->height = node_height(node);
	node->balance = node_balance(node);
	return node;
}

// Função que rotaciona o nodo "node" para a esquerda
t_node *rot_left(t_node *node) {

	t_node *aux;

	// Faz-se as trocas dos ponteiros
	aux = node->right;
	aux->parent = node->parent;
	node->parent = aux;
	
	node->right = aux->left;
	if (node->right)
		node->right->parent = node;
	aux->left = node;
	
	// Atualizam-se as alturas e fatores de balanceamento
	aux = refresh_node(aux);
	node = refresh_node(node);
	return aux;
}

// Função que rotaciona o nodo "node" para a direita
t_node *rot_right(t_node *node) {

	t_node *aux;

	// Trocam-se os ponteiros
	aux = node->left;
	aux->parent = node->parent;
	node->parent = aux;

	node->left = aux->right;
	if (node->left)
		node->left->parent = node;
	aux->right = node;
	
	// Atualizam-se as alturas e fator de balanceamento
	aux = refresh_node(aux);
	node = refresh_node(node);
	return aux;
}

// Função responsável por manter a árvore ou subárvore, com raiz "node", balanceada
t_node *fix_balance(t_node *node) {

	// Se o fator de balanceamento for menor que -1, a árvore está right heavy
	if (node->balance < -1) {
		// Se há um zig zag rotaciona-se "node->right" a direita
		if (node->right->balance > 0)
			node->right = rot_right(node->right);
		// Rotacão de "node" para a esquerda
		node = rot_left(node);

	} 
	// Se o fator for maior que 1, há um caso de left heavy
	else if (node->balance > 1) {
		// Se houver zig zag rotaciona-se "node->left" a esquerda
		if (node->left->balance < 0)
		       node->left = rot_left(node->left);
		// Rotação de "node" para a direita
		node = rot_right(node);	
	}
	
	return node;
}

// Função que varre a árvore procurando por um nodo com chave "key"
// Se não encontrar, ele é criado e inserido na árvore
t_node *insert_node(t_node *node, int key) {
	
	if (!node)
		node = new_node(key);

	// Algoritmo de busca BST
	if (key < node->key) {
		node->left = insert_node(node->left,key);
		node->left->parent = node;
	} else if (key > node->key) { 
		node->right = insert_node(node->right,key);
		node->right->parent = node;
	} else
		return node;
	
	// Calcula-se a altura do novo nodo e balanceamento
	node = refresh_node(node);
	// Arruma a árvore para manter o balanceamento
	node = fix_balance(node);

	return node;
}

t_node *remove_node(t_node *node, int key) {

	t_node *aux;
	
	if (!node)
		return node;

	if (node->key < key)
		node->right = remove_node(node->right,key);
	else if (node->key > key)
		node->left = remove_node(node->left,key);
	else {
		if ((!node->left) || (!node->right)) {
			if (node->left) {
				aux = node->left;
				node = aux;
			} else if (node->right) {
				aux = node->right;
				node = aux;
			} else {
				aux = node;
				node = NULL;
			}
			free(aux);
		} else {
			aux = node->left;
			while (aux->right)
				aux = aux->right;
			node->key = aux->key;
			node->left = remove_node(node->left,key);
		}
	}

	if (!node)
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
		

