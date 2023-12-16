// this is an example of std_lib data structure:
// red_black tree(set), heap(priority_queue)
#include <set>
#include <vector>
#include <queue>
using namespace std;

struct my {
public:
	int x;
	int y;
	static struct comp
	{
		bool operator()(my* v1, my* v2) const
		{
			return v1->x < v2->x;
		}
	};
	my(int i, int j) : x(i), y(j) {};
	bool operator< (my another) {
		return (x > another.x);
	}
};

struct rbtree {
	set<my*, my::comp> s;
	void insert(my* i) {
		s.insert(i);
	}
	my* erase(my* i) {
		s.erase(i);
		return i;
	}
	vector<my*>* sortlist() {
		vector<my*>* out = new vector<my*>({});
		for (my* i : s) {
			out->push_back(i);
		}
		return out;
	}
};

struct prior_que {
	priority_queue<my*, vector<my*>, my::comp> q = {};
	void insert(my* i) {
		q.push(i);
	}
	my* erase(my* i) {
		q.pop();
		return i;
	}
	vector<my*>* sortlist() {
		vector<my*>* out = new vector<my*>({});
		while(!q.empty()) {
			my* temp = q.top();
			q.pop();
			out->push_back(temp);
		}
		return out;
	}

};