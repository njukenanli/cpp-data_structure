class graph {
private:
    struct edge {
    public:
        edge* next;
        int idx; //dest v
        int weight;
        edge(int i, int w) : idx(i), weight(w), next(nullptr) {};
    };
    edge** edgelist; //out egde list
    int n; //node number
    void dfs(int i, bool* visited) {
        edge* temp = edgelist[i];
        while (temp != nullptr) {
            if (visited[temp->idx] == 0) {
                visited[temp->idx] = 1;
                dfs(temp->idx, visited);
            }
            temp = temp->next;
        }
        return;
    }
public:
    graph(int i) {
        n = i;
        edgelist = new edge * [i];
        for (int j = 0; j < n; j++) {
            edgelist[j] = nullptr;
        }
    }
    void insert(int i, int j, int weight) {
        if (edgelist[i] == nullptr) {
            edgelist[i] = new edge(j, weight);
        }
        else {
            edge* temp = new edge(j, weight);
            temp->next = edgelist[i];
            edgelist[i] = temp;
        }
        return;
    }
    void undirected_insert(int i, int j, int weight) {
        insert(i, j, weight);
        insert(j, i, weight);
        return;
    }
    void dfs_main() {
        bool* visited = new bool[n];
        for (int i = 0; i < n; i++) {
            visited[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                visited[i] = 1;
                dfs(i, visited);
            }
        }
        delete[] visited;
        return;
    }
};