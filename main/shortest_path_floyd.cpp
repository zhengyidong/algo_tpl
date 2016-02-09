/* floyd shortest path algorithm. */
/* time  complexity: O(n^3) */
/* space complexity: O(n^3) */
/* INF       :infinity */
/* n         :number of vertex */
/* g[][]     :original graph in adjacent matrix */
/* path[][]  :path[a][b] equals k indicates that */
/*            shortest path of a->b goes from a to k first. */
/*            optional. */
void shortest_path_floyd(int n){
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            dist[i][j] = g[i][j];
            path[i][j] = j;
        }
    }
    for(int k=1; k<=n; ++k)
      for(int i=1; i<=n; ++i)
        for(int j=1; j<=n; ++j){
           if(dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]){
               dist[i][j] = dist[i][k] + dist[k][j];
               path[i][j] = path[i][k];
           }
        }
}
