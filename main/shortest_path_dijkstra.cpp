/* Dijkstra shortest path using adjacent list. */
/* check ajacency_list.cpp to see usage of ajacent list. */
/* time  complexity: O(ElogE) */
/* space complexity: O(E) */
/* INF             : infinity */
/* n               : number of vertex. */
/* MAX_N           : max number of vertex. */
/* source          : source point */
/* d[0..n]         : d[i].dis stands for shortest distance from source to i */
/* usage           : 
      call shortest_path_dijkstra(n, source) and 
      store shortest distances in d[].dis.
*/
struct dist{
    bool operator<(const dist& b) const{
        return this->dis > b.dis;
    }
    int dis;
    int num;
};
dist d[MAX_N];
bool visited[MAX_N];
void shortest_path_dijkstra(int n, int source){
    priority_queue<dist> q;
    dist tmp;
    for(int i=0; i<n; ++i) {
        d[i].dis = INF;
        d[i].num = i;
        visited[i] = false;
    }
    d[s].dis = 0;
    q.push(d[s]);

    for(int i=0; i<n; ++i){
        while(!q.empty()){
            tmp = q.top(); q.pop();
            if(visited[tmp.num]) continue;
            break;
        }
        for(int cur=head[tmp.num]; cur!=-1; cur=e[cur].nxt){
            edge ee = e[cur];
            if(!visited[ee.y] && d[tmp.num].dis != INF && d[tmp.num].dis + ee.c < d[ee.y].dis){
                d[ee.y].dis = d[tmp.num].dis + ee.c;
                q.push({d[ee.y].dis, ee.y});
            }
        }
        visited[tmp.num] = true;
    }
}
