#include "headers/graph.h"
#include "headers/heap.h"
#include "headers/ufset.h"
#include <iostream>
#include <vector>

typedef struct { int s; int e; } e;

struct mst_graph : public graph {
private:
    void dfs(int i, bool* visited, int* mst, int parent) 
    {
        mst[i] = parent;
        edge* temp = edgelist[i];
        while (temp != nullptr) {
            if (visited[temp->idx] == 0) {
                visited[temp->idx] = 1;
                dfs(temp->idx, visited, mst, i);
            }
            temp = temp->next;
        }
        return;
    }
public:
    mst_graph(int n) :graph(n) {};
    int* dfs_main()
    {
        bool* visited = new bool[n];
        int* mst = new int[n];
        for (int i = 0; i < n; i++) {
            visited[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                visited[i] = 1;
                dfs(i, visited, mst, -1);
            }
        }
        delete[] visited;
        return mst;
    }
};

/*
//undirected graph
9
//node numbder n
//format: for each node i=0 ..., n-1
//k related edges, edge1(destination, weight), edge2(destination, weight) ...
3    1 2    5 7    6 3
3    0 2    2 4    6 6
3    1 4    3 2    7 2
3    2 2    4 1    7 8
3    3 1    5 6    8 2
3    0 7    4 6    8 5
4    0 3    1 6    7 3    8 1
4    2 2    3 8    6 3    8 4
4    4 2    5 5    6 1    7 4
*/

inline void kruskal() {
    int n;
    std::cin >> n;
    int count;
    int idx = 0;
    int dst, weight;
    std::vector<heap::node*> sortlist(0);
    std::vector<e> edgelist(0);
    for (int i = 0; i < n; i++) {
        std::cin >> count;
        for (int j = 0; j < count; j++) {
            std::cin >> dst >> weight;
            if (i < dst) {
                sortlist.push_back(new heap::node(idx,weight));
                edgelist.push_back({ i,dst });
                idx++;
            }
        }
    }
    heap h(idx, sortlist);
    heap::node** ans = h.heapsort();

    int top = 0;
    ufset ufs(n);
    count = 0;
    mst_graph mstg(n);
    e temp;
    while (count < n - 1) {
        temp = edgelist[ans[top]->id];
        if (ufs.cfind(temp.s) != ufs.cfind(temp.e)) {
            mstg.undirected_insert(temp.s, temp.e, ans[top]->v);
            ufs.wunion(temp.s, temp.e);
            count++;
        }
        top++;
    }
    int* mst = mstg.dfs_main();
    for (int i = 0; i < n; i++) {
        std::cout<< mst[i] <<' ';
    }
    delete[] mst;
    std::cout << std::endl;
}