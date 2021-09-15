typedef struct Tree{
	int freq;
	unsigned char symb;
	char code[256];
	struct Tree *left;
	struct Tree *right;
}Tree;
Tree *create_node(unsigned char c, int fr, Tree *left_son, Tree *right_son){
	Tree *t = (Tree*)malloc(sizeof(Tree));
	t->freq = fr;
	t->symb = c;
	t->left = left_son;
	t->right = right_son;
	return t;
}
void free_tree(Tree *t){
	if (t->left)
		free_tree(t->left);
	if (t->right)
		free_tree(t->right);
	free(t);
}
