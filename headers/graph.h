class graph {
protected:
    struct edge {
    public:
        edge* next;
        int idx; //dest v
        int weight;
        edge(int i, int w) : idx(i), weight(w), next(nullptr) {};
    };
    struct node {
        int idx;
        int weight;
        node(int i) : idx(i), weight(-1) {};
        node(int i, int j) : idx(i), weight(j) {};
    };
    edge** edgelist; //out egde list
    node** nodelist; //save vertex info
    int n; //node number
private:
    void dfs(int i, bool* visited) //function type can also be rewritten in a inherited class
    {
        //pre_order process
        //you can insert process codes here in a rewritten function in a inherited class
        edge* temp = edgelist[i];
        while (temp != nullptr) {
            if (visited[temp->idx] == 0) {
                visited[temp->idx] = 1;
                //in_order process
                //you can insert process codes here in a rewritten function in a inherited class
                dfs(temp->idx, visited);
                //you can insert process codes here in a rewritten function in a inherited class
            }
            temp = temp->next;
        }
        //post_order process
        //you can insert process codes here in a rewritten function in a inherited class
        return;
    }
public:
    graph(int i) {
        n = i;
        edgelist = new edge * [i];
        nodelist = new node * [i];
        for (int j = 0; j < n; j++) {
            edgelist[j] = nullptr;
            nodelist[j] = new node(j);
        }
    }
    ~graph() {
        for (int i = 0; i < n; i++) {
            edge* temp = edgelist[i];
            edge* next;
            while (temp != nullptr) {
                next = temp->next;
                delete temp;
                temp = next;
            }
            delete nodelist[i];
        }
        delete[] edgelist;
        delete[] nodelist;
    }
    void directed_insert(int i, int j, int weight = -1) {
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
    void undirected_insert(int i, int j, int weight = -1) {
        directed_insert(i, j, weight);
        directed_insert(j, i, weight);
        return;
    }
    void dfs_main() //function type can also be rewritten in a inherited class
    {
        bool* visited = new bool[n];
        for (int i = 0; i < n; i++) {
            visited[i] = 0;
            //you can insert process codes here in a rewritten function in a inherited class
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                visited[i] = 1;
                //you can insert process codes here in a rewritten function in a inherited class
                dfs(i, visited);
                //you can insert process codes here in a rewritten function in a inherited class
            }
        }
        delete[] visited;
        //you can insert process codes here in a rewritten function in a inherited class
        return;
    }
};