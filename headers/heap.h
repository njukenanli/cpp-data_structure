#include <vector>

struct heap {
public:
	struct node {
	public:
		int id;
		int v;
		node(int i, int j) : id(i), v(j) {};
	};
	heap(int cursize, std::vector<node*> t) {
		tree = std::vector<node*>(cursize);
		for (int i = 0; i < cursize; i++) {
			tree[i] = t[i];
		}
		size = cursize;
		construct();
	}
	heap() {
		tree = std::vector<node*>(0);
		size = 0;
	}
	bool comp(node* i, node* j) {
		return (i->v < j->v);
	}
	void construct() {
		int curp = (size - 2) / 2;
		while (curp >= 0) {
			siftdown(curp, tree[curp]);
			curp--;
		}
	}
	void siftup(int p, node* newnode) {
		if (p == 0) return;
		int father = (p - 1) / 2;
		while (true) {
			if (comp(newnode, tree[father])) {
				tree[p] = tree[father];
				p = father;
				father = (p - 1) / 2;
				if (p == 0) break;
			}
			else break;
		}
		tree[p] = newnode;
	}
	void siftdown(int p, node* newnode) {
		int lchild = 2 * p + 1;
		int rchild = 2 * p + 2;
		node* min;
		while (lchild < size) {
			if (rchild >= size) {
				if (comp(tree[lchild], newnode)) {
					tree[p] = tree[lchild];
					p = lchild;
					break;
				}
				else break;
			}
			min = comp(tree[lchild], tree[rchild]) ? tree[lchild] : tree[rchild];
			if (comp(newnode, min)) {
				break;
			}
			else {
				if (comp(tree[rchild], tree[lchild])) {
					tree[p] = tree[rchild];
					p = rchild;
					lchild = 2 * p + 1;
					rchild = 2 * p + 2;
				}
				else {
					tree[p] = tree[lchild];
					p = lchild;
					lchild = 2 * p + 1;
					rchild = 2 * p + 2;
				}
			}
		}
		tree[p] = newnode;
	}
	node* delroot() {
		if (!empty()) {
			node* r = tree[0];
			node* newnode = tree[size - 1];
			size--;
			siftdown(0, newnode);
			return r;
		}
		else return nullptr;
	}
	void insert(node* i) {
		tree[size] = i;
		size++;
		siftup(size - 1, i);
	}
	bool empty() {
		return size == 0;
	}
	node* getroot() {
		if (!empty()) return tree[0];
		else return nullptr;
	}
	node** heapsort() {
		node** ans = new node * [size];
		for (int i = 0; !empty(); i++) {
			ans[i] = delroot();
		}
		return ans;
	}
private:
	int size;
	int msize;
	std::vector<node*> tree;
};
