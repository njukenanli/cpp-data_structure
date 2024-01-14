//#define KODARAJU
#define KRUSKAL

#ifdef KODARAJU
#include "kosaraju.cpp"
extern void kosaraju();
#endif 

#ifdef KRUSKAL
#include "kruskal.cpp"
extern void kruskal();
#endif

int main() {
#ifdef KODARAJU
	kosaraju();
#endif

#ifdef KRUSKAL
	kruskal();
#endif
	return 0;
}