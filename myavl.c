// Luan Machado Bernardt | GRR20190363

#include <stdio.h>
#include "avl.h"

int main () {

	t_node *avl = NULL;
	char c;
	int num;

	// Função que lê stdin até encontrar o fim do arquivo (EOF ou ctrl+d)
	while ((c = getchar()) != EOF) {
		switch (c) {
			// Se ler i, lê-se um espaço em branco e em seguida o número a ser inserido
			case 'i':
				c = getchar();
				scanf("%d",&num);
				avl = insert_node(avl,num);
				break;
			// Se r, l~e-se um espaço em branco e em seguida o número a ser removido
			case 'r':
				c = getchar();
				scanf("%d",&num);
				avl = remove_node(avl,num);
				break;
		}
	}
	in_order(avl);
	return 1;
}
