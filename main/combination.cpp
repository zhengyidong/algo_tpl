/* calculate C(n, m), number of k-combinations from a given set S of n elements. */
/* time  complexity: O(m) */
/* space complexity: O(1) */
/* usage             :just use it. */
int C(int n, int m){
    if(m > n - m) m = n - m;
    int ans = 1;
    for(int i=0; i<m; ++i){
      ans *= n - i;
      ans /= i + 1;
    }
    return ans;
}
