struct node {
public:
	int s;
	int e;
	int v;
	node(int i, int j, int k) : s(i), e(j), v(k) {};
};

struct heap {
private:
	int size;
	node** tree;
public:
	heap(int s, node** t) {
		tree = t;
		size = s;
		construct();
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
		node* r = tree[0];
		node* newnode = tree[size - 1];
		size--;
		siftdown(0, newnode);
		return r;
	}
	bool empty() {
		return size == 0;
	}
	node* getroot() {
		if (!empty()) return tree[0];
		else return nullptr;
	}
};
