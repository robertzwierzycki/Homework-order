// AiSD_Projekt_nr3.cpp 
//

#include "stdafx.h"
#include <iostream>

struct module {
	int value;
	module *parent, *right, *left;
};

struct tree {
	module *root;
	tree() {
		root = NULL;
	}
	void getTree(module *x, int n);
	void addModule(int val) {
		module *newModule = new module;
		newModule->value = val;
		newModule->right = NULL;
		newModule->left = NULL;
		//if first element
		if (root == NULL) {
			root = newModule;
			newModule->parent = NULL;
		}
		else {
			module *tmp = new module;
			tmp = root;
			while (1) {
				if (val > tmp->value) {
					if (tmp->right == NULL) {
						newModule->parent = tmp;
						tmp->right = newModule;
						break;
					}
					else {
						//go deeper
						tmp = tmp->right;
					}
				}
				else {
					if (tmp->left == NULL) {
						newModule->parent = tmp;
						tmp->left = newModule;
						break;
					}
					else {
						//go deeper
						tmp = tmp->left;
					}
				}
			}
		}
	}
	void changeValue(int Ov, int Nv) {
		if (delateModule(Ov) == true) {
			addModule(Nv);
		}
		else {
			printf("na\n");
		}
	}
	void printTree(module *x) {
		if (x == NULL) {
			return;
		}
		printTree(x->right);
		printf("%d\n", x->value);
		printTree(x->left);
	}
	void printMax() {
		module *tmp = new module;
		tmp = root;
		if (root != NULL) {
			while (1) {
				if (tmp->right == NULL) {
					printf("%d\n", tmp->value);
					delateModule(tmp->value);
					break;
				}
				else {
					tmp = tmp->right;
				}
			}
		}
	}
	void transplant(module *u, module *v) {
		if (u->parent == NULL) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		if (v != NULL) {
			v->parent = u->parent;
		}
	}
	bool delateModule(int value) {
		module *tmp = new module;
		tmp = root;
		while (1) {
			if (value < tmp->value) {
				if (tmp->left != NULL) {
					tmp = tmp->left;
				}
				else {
					//not find the value
					return false;
				}
			}
			else if (value > tmp->value) {
				if (tmp->right != NULL) {
					tmp = tmp->right;
				}
				else {
					//not find the value
					return false;
				}
			}
			//found correct node
			else {
				//if no child
				if (tmp->left == NULL && tmp->right == NULL) {
					if (tmp == root) {
						root = NULL;
					}
					else if (tmp->parent->left == tmp) {
						tmp->parent->left = NULL;
					}
					else {
						tmp->parent->right = NULL;
					}
					return true;
				}
				//if 1 child
				else if (tmp->left == NULL && tmp->right != NULL) {
					if (tmp == root) {
						root = tmp->right;
						tmp->right->parent = NULL;
					}
					else if (tmp->parent->left == tmp) {
						tmp->parent->left = tmp->right;
					}
					else {
						tmp->parent->right = tmp->right;
					}
					tmp->right->parent = tmp->parent;
					return true;
				}
				else if (tmp->left != NULL && tmp->right == NULL) {
					if (tmp == root) {
						root = tmp->left;
						tmp->left->parent = NULL;
					}
					else if (tmp->parent->left == tmp) {
						tmp->parent->left = tmp->left;
					}
					else {
						tmp->parent->right = tmp->left;
					}
					tmp->left->parent = tmp->parent;
					return true;
				}
				//if 2 children
				else {
					module *tmp2 = new module;
					tmp2 = tmp->right;
					while (tmp2->left != NULL) {
						tmp2 = tmp2->left;
					}
					if (tmp2->parent != tmp) {
						transplant(tmp2, tmp2->right);
						tmp2->right = tmp->right;
						tmp2->right->parent = tmp2;
					}
					transplant(tmp, tmp2);
					tmp2->left = tmp->left;
					tmp->left->parent = tmp2;
					return true;
				}
			}
		}
	}
};
tree *tab = new tree[1000];
void tree::getTree(module *x, int n) {
	if (x == NULL) {
		return;
	}
	getTree(x->left, n);
	tab[n].addModule(x->value);
	getTree(x->right, n);
}

int main()
{
	int N, arg1, arg2, arg3;
	char znak;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf(" %c", &znak);
		switch (znak)
		{
		case 'a':
			//a group value - Add element with value to the group
			scanf("%d %d", &arg1, &arg2);
			tab[arg1].addModule(arg2);
			break;
		case 'e':
			//e group - Extract element with maximum value from the group and print it's value
			scanf("%d", &arg1);
			if (tab[arg1].root != NULL) {
				tab[arg1].printMax();
			}
			else {
				printf("na\n");
			}
			break;
		case 'p':
			//p group - Print values of all elements in the group according to their decreasing
			scanf("%d", &arg1);
			if (tab[arg1].root != NULL) {
				tab[arg1].printTree(tab[arg1].root);
			}
			else {
				printf("na\n");
			}
			break;
		case 'm':
			//m group1 group2 - Merge groups 1 and 2.
			scanf("%d %d", &arg1, &arg2);
			if (tab[arg2].root != NULL) {
				tab[arg2].getTree(tab[arg2].root, arg1);
				tab[arg2].root = NULL;
			}
			else {
				printf("na\n");
			}
			break;
		case 'i':
			//i group oldValue newValue - increase value of element in group from oldValue to newValue
			scanf("%d %d %d", &arg1, &arg2, &arg3);
			if (tab[arg1].root != NULL) {
				tab[arg1].changeValue(arg2, arg3);
			}
			else {
				printf("na\n");
			}
			break;
		}
	}

	//system("pause");
	return 0;
}