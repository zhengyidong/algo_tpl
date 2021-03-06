/* kruskal's algorithm for minimum spanning tree(MST). */
/* use lambda for convenience. */
/* time  complexity: O(ElogV) */
/* space complexity: O(E + V) */
/* INF              : MST is INF(infinity) means that the graph is not connected*/
/* MAX_M            : maximum number of edges */
/* m                : number of edges */
/* n                : number of vertices */
/* ed[0..m-1]       : edges */
/* s                : disjoint set. check
 *                    disjoint_set.cpp for usage. */
/* edge::x, edge::y : the endpoints of edge */
/* edge::c          : the weight of edge */
/* on_tree[i]       : if the edge i is on our MST. */
/* usege:           just call it after edge[] being filled.*/
/*
 * NOTE : replace the calculation of 'ans' to the commented line when
 *        calculating the bottleneck of bottleneck spanning tree.
 */

struct edge{
    int x, y, c;
}ed[MAX_M];

bool on_tree[MAX_M];

int mst_kruskal(){
    memset(on_tree, false, sizeof(on_tree));

    sort(ed, ed + m, [](const edge& e1, const edge& e2){
        return e1.c < e2.c;
    });

    disjoint_set s;
    int ans = 0;
    int num_edges = 0;

    for(int i=0; i<m; ++i){
        if(s.find(ed[i].x) != s.find(ed[i].y)){
            s.merge(ed[i].x, ed[i].y);
            on_tree[i] = true;
            ans += ed[i].c;
            ++num_edges;
            // ans = max(ans, ed[i].c); for bottleneck spanning tree
        }
    }
	if(num_edges != n - 1) return INF;

    return ans;
}
