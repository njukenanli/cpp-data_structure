#include "headers/graph.h"
#include <iostream>
typedef struct { int* finishstk; int top; } RETTYPE;

struct scc_graph : public graph {
private:
	void stack_dfs(int i, edge** edgelist, int* finishstk,
		int& top, bool* visited) {
		edge* temp = edgelist[i];
		while (temp != nullptr) {
			if (visited[temp->idx] == 0) {
				visited[temp->idx] = 1;
				stack_dfs(temp->idx, edgelist, finishstk, top, visited);
			}
			temp = temp->next;
		}
		finishstk[top] = i;
		top++;
		return;
	}
	void trans_dfs(int i, int leader, edge** edgelist, bool* visited, int* scc) {
		scc[i] = leader;
		edge* temp = edgelist[i];
		while (temp != nullptr) {
			if (visited[temp->idx] == 0) {
				visited[temp->idx] = 1;
				trans_dfs(temp->idx, leader, edgelist, visited, scc);
			}
			temp = temp->next;
		}
		return;
	}

public:
	scc_graph(int n) :graph(n) {};

	RETTYPE stack_dfs_main() {
		int* finishstk = new int[n];
		int top = 0; //[0,top)
		bool* visited = new bool[n];
		for (int i = 0; i < n; i++) {
			visited[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			if (visited[i] == 0) {
				visited[i] = 1;
				stack_dfs(i, edgelist, finishstk, top, visited);
			}
		}
		delete[] visited;
		return {finishstk, top};
	}
	
	int* trans_dfs_main(int* finishstk, int top) {
		bool* visited = new bool[n];
		for (int i = 0; i < n; i++) {
			visited[i] = 0;
		}
		int leader;
		int* scc = new int[n];
		while (top > 0) {
			top--;
			leader = finishstk[top];
			if (visited[leader] == 0) {
				visited[leader] = 1;
				trans_dfs(leader, leader, edgelist, visited, scc);
			}
		}
		delete[] visited;
		delete[] finishstk;
		return scc;
	}

};

/*
7 //number of vertices
//format: k out_edges; destination vertex of out_edge 1, 2...k
3    1    2    5
2    2    3
0
2    0    2
1    6
2    0    2
1    4
*/

inline void kosaraju() {
	int n;
	std::cin >> n;
	int k, dst;
	scc_graph* g = new scc_graph(n);
	scc_graph* trans_g = new scc_graph(n);
	for (int i = 0; i < n; i++) {
		std::cin >> k;
		for (int j = 0; j < k; j++) {
			std::cin >> dst;
			g->directed_insert(i, dst);
			trans_g->directed_insert(dst, i);
		}
	}
	RETTYPE res = g->stack_dfs_main();
	int* scc = trans_g->trans_dfs_main(res.finishstk, res.top);
	for (int i = 0; i < n; i++) {
		std::cout << scc[i] << ' ';
	}
	delete[] scc;
	return;
}