#include <iostream>
using namespace std;

struct bst {
private:
	struct node {
	public:
		int v;
		node* l;
		node* r;
		node(int i) : v(i), l(nullptr), r(nullptr) {};
	};
	node* root;
	int maxsize;
public:
	bst(int n, int s) {
		root = new node(n);
		maxsize = s;
	}
	void insert(int i) {
		node* p = root;
		while (true) {
			if (i > p->v) {
				if (p->r != nullptr) p = p->r;
				else {
					p->r = new node(i);
					break;
				}
			}
			else {
				if (p->l != nullptr) p = p->l;
				else {
					p->l = new node(i);
					break;
				}
			}
		}
	}
	void find(int i, node*& p, node*& cur) {
		node* tempfather = nullptr;
		node* temp = root;
		while (true) {
			if (i == temp->v) {
				p = tempfather;
				cur = temp;
				return;
			}
			else if (i > temp->v) {
				if (temp->r != nullptr) {
					tempfather = temp;
					temp = temp->r;
				}
				else return;
			}
			else {
				if (temp->l != nullptr) {
					tempfather = temp;
					temp = temp->l;
				}
				else return;
			}
		}
	}
	void del(int i) {
		node* cur = nullptr;
		node* p = nullptr;
		find(i, p, cur);
		if (cur->l == nullptr || cur->r == nullptr) {
			node* next = (cur->l != nullptr) ? cur->l : cur->r;
			if (cur != root)
			{
				if (p->l == cur) p->l = next;
				else p->r = next;
			}
			else root = next;
			delete cur;
		}
		else {
			node* maxnode = nullptr;
			node* maxp = nullptr;
			sepmax(cur, cur->l, maxp, maxnode);  //get the max value in the left tree
			maxnode->l = cur->l;
			maxnode->r = cur->r; //link children
			if (cur != root) {
				if (p->l == cur) p->l = maxnode;
				else p->r = maxnode; //link parent
			}
			else root = maxnode;
			delete cur;
		}
	}
	void sepmax(node* rt, node* left, node*& maxp, node*& maxnode) {
		node* p = rt;
		node* cur = left;
		while (true) {
			if (cur->r == nullptr) {
				if (p->l == cur) {
					p->l = cur->l; //cur's 2 children = nullptr or cur only has sigle left child
				}
				else {
					p->r = cur->l;
				}
				maxp = p;
				maxnode = cur;
				return;
			}
			else {
				p = cur;
				cur = cur->r;
			}
		}

	}
	void BFS() {
		node** q = new node * [maxsize];
		int front = 0, rear = 0;
		q[rear] = root;
		rear++;
		node* cur;
		while (front != rear) {
			cur = q[front];
			front++;
			cout << cur->v;
			cout << " ";
			if (cur->l != nullptr) {
				q[rear] = cur->l;
				rear++;
			}
			if (cur->r != nullptr) {
				q[rear] = cur->r;
				rear++;
			}
		}
		cout << endl;
		delete[] q;
	}
};