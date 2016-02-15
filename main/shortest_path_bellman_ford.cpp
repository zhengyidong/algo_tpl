/* Bellman-Ford shortest path using adjacent list. */
/* check ajacent_list.cpp to see usage of ajacent list. */
/* time  complexity: O(VE) */
/* space complexity: O(E) */
/* INF             : infinity */
/* n               : number of vertex. */
/* source          : source point */
/* dist[0..n]      : dist[i] stands for shortest distance from source to i */
/* usage           : 
      returns false if the graph contains negative-weight cycle,
      returns true and store shortest distances in dist otherwise.
*/

bool shortest_path_bellman_ford(int n, int source){
    for(int i=0; i<n; ++i){
        dist[i] = INF;
    }
    dist[source] = 0;
    int i = 0;
    for(; i<n; ++i){
        bool updated = false;
        for(int j=0; j<n; ++j){
            for(int cur=head[j]; cur!=-1; cur=e[cur].nxt){
                int y = e[cur].y;
                if(y == source) continue;
                if(dist[j] != INF && dist[y] > dist[j] + e[cur].c){
                    dist[y] = dist[j] + e[cur].c;
                    updated = true;
                }
            }
        }

        if(!updated) break;
    }
    if(i == n) return false;
    return true;
}

