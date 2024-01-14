class ufset {
private:
    int* a;
    int size;
public:
    ufset(int s) {
        size = s;
        a = new int[s];
        for (int i = 0; i < s; i++) {
            a[i] = -1;
        }
    }
    ~ufset() {
        delete[] a;
    }
    int cfind(int x) //compressed find
    {
        if (x < 0 || x >= size) return -1;
        int p = x;
        while (a[p] >= 0) {
            p = a[p];
        }
        int father = p;
        p = x;
        int temp;
        if (a[p] >= 0) {
            while (a[p] != father) {
                temp = a[p];
                a[p] = father;
                p = temp;
            }
        }
        return father;
    }
    bool wunion(int x, int y) 
    //weighted union: the tree with fewer nodes will be the child tree
    {
        int rootx = cfind(x);
        int rooty = cfind(y);
        if (rootx == -1 || rooty == -1) return 0;
        if (rootx == rooty) return 0;
        if (a[rootx] >= a[rooty]) {
            a[rootx] += a[rooty];
            a[rooty] = rootx;
        }
        else {
            a[rooty] += a[rootx];
            a[rootx] = rooty;
        }
        return 1;
    }
};