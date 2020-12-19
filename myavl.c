#include <stdio.h>
#include "avl.h"

int main () {

	t_node *avl = NULL;
	char c;
	int num;

	while ((c = getchar()) != EOF) {
		switch (c) {
			case 'i':
				c = getchar();
				scanf("%d",&num);
				avl = insert_node(avl,num);
				break;
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
