#include "AvlTree.h"
AvlTree::AvlTree() : root{ nullptr }
{ }

AvlTree::AvlTree(const AvlTree & rhs) : root{ nullptr }
{
	root = clone(rhs.root);
}

AvlTree::AvlTree(AvlTree && rhs) : root{ rhs.root }
{
	rhs.root = nullptr;
}

AvlTree::~AvlTree()
{
	makeEmpty();
}

const int & AvlTree::findMin() const
{
	if (isEmpty())
		return -1;
	return findMin(root)->element;
}

const int& AvlTree::findMax() const
{
	if (isEmpty())
		return -1;
	return findMax(root)->element;
}

bool AvlTree::contains(const int& x) const
{
	return contains(x, root);
}

bool AvlTree::isEmpty() const
{
	return root == nullptr;
}

void AvlTree::printTree() const
{
	if (isEmpty())
		cout << "Empty tree" << endl;
	else
		printTree(root);
}

void AvlTree::makeEmpty()
{
	makeEmpty(root);
}

void AvlTree::insert(const int& x)
{
	insert(x, root);
}

void AvlTree::insert(int&& x)
{
	insert(std::move(x), root);
}

void AvlTree::remove(const int& x)
{
	remove(x, root);
}

void AvlTree::insert(const int& x, AvlNode * & t)
{
	if (t == nullptr)
		t = new AvlNode{ x, nullptr, nullptr };
	else if (x < t->element)
		insert(x, t->left);
	else if (t->element < x)
		insert(x, t->right);

	balance(t);
}

void AvlTree::insert(int && x, AvlNode * & t)
{
	if (t == nullptr)
		t = new AvlNode{ std::move(x), nullptr, nullptr };
	else if (x < t->element)
		insert(std::move(x), t->left);
	else if (t->element < x)
		insert(std::move(x), t->right);

	balance(t);
}

void AvlTree::remove(const int& x, AvlNode * & t)
{
	if (t == nullptr)
		return;   // Item not found; do nothing

	if (x < t->element)
		remove(x, t->left);
	else if (t->element < x)
		remove(x, t->right);
	else if (t->left != nullptr && t->right != nullptr) // Two children
	{
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else
	{
		AvlNode *oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}

	balance(t);
}

void AvlTree::balance(AvlNode * & t)
{
	if (t == nullptr)
		return;

	if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
		if (height(t->left->left) >= height(t->left->right))
			rotateWithLeftChild(t);
		else
			doubleWithLeftChild(t);
	else
		if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
			if (height(t->right->right) >= height(t->right->left))
				rotateWithRightChild(t);
			else
				doubleWithRightChild(t);

	t->height = max(height(t->left), height(t->right)) + 1;
}

AvlNode * AvlTree::findMin(AvlNode *t) const
{
	if (t == nullptr)
		return nullptr;
	if (t->left == nullptr)
		return t;
	return findMin(t->left);
}

AvlNode * AvlTree::findMax(AvlNode *t) const
{
	if (t != nullptr)
		while (t->right != nullptr)
			t = t->right;
	return t;
}

bool AvlTree::contains(const int& x, AvlNode *t) const
{
	if (t == nullptr)
		return false;
	else if (x < t->element)
		return contains(x, t->left);
	else if (t->element < x)
		return contains(x, t->right);
	else
		return true;    // Match
}

void AvlTree::makeEmpty(AvlNode * & t)
{
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}

void AvlTree::printTree(AvlNode *t) const
{
	if (t != nullptr)
	{
		printTree(t->left);
		cout << t->element << endl;
		printTree(t->right);
	}
}

AvlNode * AvlTree::clone(AvlNode *t) const
{
	if (t == nullptr)
		return nullptr;
	else
		return new AvlNode{ t->element, clone(t->left), clone(t->right), t->height };
}

int AvlTree::height(AvlNode *t) const
{
	return t == nullptr ? -1 : t->height;
}

int AvlTree::max(int lhs, int rhs) const
{
	return lhs > rhs ? lhs : rhs;
}

void AvlTree::rotateWithLeftChild(AvlNode * & k2)
{
	AvlNode *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}

void AvlTree::rotateWithRightChild(AvlNode * & k1)
{
	AvlNode *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;
	k1 = k2;
}

void AvlTree::doubleWithLeftChild(AvlNode * & k3)
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

void AvlTree::doubleWithRightChild(AvlNode * & k1)
{
	rotateWithLeftChild(k1->right);
	rotateWithRightChild(k1);
}