#include <iostream>

enum Color{Black,Red};

template <class T>
struct TNode{
	T key;
	Color color;
	TNode<T> *left;
	TNode<T> *right;
	TNode<T> *parent;
	TNode(T k, Color c, TNode *p, TNode *l, TNode *r) : key(k), color(c), parent(p), left(l), right(r){};
};

template <class T>
class RBTree{
public:
	RBTree();
	~RBTree();

	void insert(T key);
	void remove(T key);
	TNode<T> *search(T key);
	void print();

private:
	void onLeft(TNode<T> *&root, TNode<T> *x);
	void onRight(TNode<T> *&root, TNode<T> *y);

	void insert(TNode<T> *&root, TNode<T> *node);
	void insert2(TNode<T> *&root, TNode<T> *node);
	void DeleteTree(TNode<T> *&node);

	void remove(TNode<T> *&root, TNode<T> *node);
	void remove2(TNode<T> *&root, TNode<T> *node, TNode<T> *parent);

	TNode<T> *search(TNode<T> *node, T key) const;
	void print(TNode<T> *node) const;

private:
	TNode<T> *root;
};

template <class T>
RBTree<T>::RBTree() : root(NULL){
	root = nullptr;
}
template <class T>
RBTree<T>::~RBTree(){
	//DeleteTree(root);
}
template <class T>
void RBTree<T>::onLeft(TNode<T> *&root, TNode<T> *x){
	TNode<T> *y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
};
template <class T>
void RBTree<T>::onRight(TNode<T> *&root, TNode<T> *y){
	TNode<T> *x = y->left;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL)
		root = x;
	else{
		if (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
};
template <class T>
void RBTree<T>::insert(T key){
	TNode<T> *z = new TNode<T>(key, Red, NULL, NULL, NULL);
	insert(root, z);
};
template <class T>
void RBTree<T>::insert(TNode<T> *&root, TNode<T> *node){
	TNode<T> *x = root;
	TNode<T> *y = NULL;
	while (x != NULL){
		y = x;
		if (node->key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	node->parent = y;
	if (y != NULL){
		if (node->key > y->key)
			y->right = node;
		else
			y->left = node;
	}
	else
		root = node;
	node->color = Red;
	insert2(root, node);
};
template <class T>
void RBTree<T>::insert2(TNode<T> *&root, TNode<T> *node){
	TNode<T> *parent;
	parent = node->parent;
	while (node != RBTree::root && parent->color == Red){
		TNode<T> *gparent = parent->parent;
		if (gparent->left == parent){
			TNode<T> *uncle = gparent->right;
			if (uncle != NULL && uncle->color == Red){
				parent->color = Black;
				uncle->color = Black;
				gparent->color = Red;
				node = gparent;
				parent = node->parent;
			}
			else{
				if (parent->right == node){
					onLeft(root, parent);
					swap(node, parent);
				}
				onRight(root, gparent);
				gparent->color = Red;
				parent->color = Black;
				break;
			}
		}
		else{
			TNode<T> *uncle = gparent->left;
			if (uncle != NULL && uncle->color == Red){
				gparent->color = Red;
				parent->color = Black;
				uncle->color = Black;

				node = gparent;
				parent = node->parent;
			}
			else{
				if (parent->left == node){
					onRight(root, parent);
					swap(parent, node);
				}
				onLeft(root, gparent);
				parent->color = Black;
				gparent->color = Red;
				break;
			}
		}
	}
	root->color = Black;
}
template <class T>
void RBTree<T>::DeleteTree(TNode<T> *&node){
	if (node == NULL)
		return;
	DeleteTree(node->left);
	DeleteTree(node->right);
	delete node;
	node = nullptr;
}

template <class T>
void RBTree<T>::remove(T key){
	TNode<T> *deletenode = search(root, key);
	if (deletenode != NULL)
		remove(root, deletenode);
}
template <class T>
void RBTree<T>::remove(TNode<T> *&root, TNode<T> *node){
	TNode<T> *child, *parent;
	Color color;
	if (node->left != NULL && node->right != NULL){
		TNode<T> *replace = node;
		replace = node->right;
		while (replace->left != NULL){
			replace = replace->left;
		}
		if (node->parent != NULL){
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			root = replace;
		child = replace->right;
		parent = replace->parent;
		color = replace->color;
		if (parent == node)
			parent = replace;
		else{
			if (child != NULL)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == Black)
			remove2(root, child, parent);

		delete node;
		return;
	}
	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;
	if (child){
		child->parent = parent;
	}
	if (parent){
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		RBTree::root = child;

	if (color == Black){
		remove2(root, child, parent);
	}
	delete node;
}
template <class T>
void RBTree<T>::remove2(TNode<T> *&root, TNode<T> *node, TNode<T> *parent){
	TNode<T> *othernode;
	while ((!node) || node->color == Black && node != RBTree::root){
		if (parent->left == node){
			othernode = parent->right;
			if (othernode->color == Red){
				othernode->color = Black;
				parent->color = Red;
				onLeft(root, parent);
				othernode = parent->right;
			}
			else{
				if (!(othernode->right) || othernode->right->color == Black){
					othernode->left->color = Black;
					othernode->color = Red;
					onRight(root, othernode);
					othernode = parent->right;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->right->color = Black;
				onLeft(root, parent);
				node = root;
				break;
			}
		}
		else{
			othernode = parent->left;
			if (othernode->color == Red){
				othernode->color = Black;
				parent->color = Red;
				onRight(root, parent);
				othernode = parent->left;
			}
			if ((!othernode->left || othernode->left->color == Black) && (!othernode->right || othernode->right->color == Black)){
				othernode->color = Red;
				node = parent;
				parent = node->parent;
			}
			else{
				if (!(othernode->left) || othernode->left->color == Black){
					othernode->right->color = Black;
					othernode->color = Red;
					onLeft(root, othernode);
					othernode = parent->left;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->left->color = Black;
				onRight(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = Black;
}

template <class T>
TNode<T> *RBTree<T>::search(T key){
	return search(root, key);
}
template <class T>
TNode<T> *RBTree<T>::search(TNode<T> *node, T key) const{
	if (node == NULL || node->key == key)
		return node;
	else if (key > node->key)
		return search(node->right, key);
	else
		return search(node->left, key);
}
template <class T>
void RBTree<T>::print(){
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		print(root);
}
template <class T>
void RBTree<T>::print(TNode<T> *node) const{
	if (node == NULL)
		return;
	if (node->parent == NULL)
		cout << node->key << "(" << node->color << ") is root" << endl;
	else if (node->parent->left == node){
		cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s "
			 << "left child" << endl;
	}
	else{
		cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s "
			 << "right child" << endl;
	}
	print(node->left);
	print(node->right);
}
