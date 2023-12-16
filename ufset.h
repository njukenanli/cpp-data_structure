class ufset {
private:
    int* a;
public:
    ufset(int size) {
        a = new int[size];
        for (int i = 0; i < size; i++) {
            a[i] = -1;
        }
    }
    int cfind(int x) {
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
    void wunion(int x, int y) {
        int rootx = cfind(x);
        int rooty = cfind(y);
        if (rootx == rooty) return;
        if (a[rootx] >= a[rooty]) {
            a[rootx] += a[rooty];
            a[rooty] = rootx;
        }
        else {
            a[rooty] += a[rootx];
            a[rootx] = rooty;
        }
    }
};