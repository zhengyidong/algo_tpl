/* a simple adjacent list. */
/* MAX_M           : maximum number of edges*/
/* MAX_N           : maximum number of vertex*/
/* ne              : number of edges. */
/* e[0..MAX_M-1]   : array storing all edges. 
                     x -> start vertex. y -> end vertex. c -> weight of edge.
                     next -> pointer to next edge goes from vertex x.*/
/* head[0..MAX_N-1]: head[i] stands for headers of vertex i */
/* usage           : 
     1. init head[] to -1, e.g. memset(head, -1, sizeof(head));
     2. init ne to 0, e.g. ne = 0;
     3. use add_edge(start, end, weight) to add edges to list.
     4. use
           for(int cur=head[i]; cur!=-1; cur=e[cur].nxt){
                ...
           }
        loop to traverse
        edges goes from i.

     you can modify type of weight as you wish.
*/
int ne;

struct edge{
    int x;
    int y;
    int c;
    int nxt;
}e[MAX_M];
int head[MAX_N];

void add_edge(int x, int y, int c){
    e[ne].x = x; e[ne].y = y; e[ne].c = c;
    e[ne].nxt = head[x]; head[x] = ne++;
}
