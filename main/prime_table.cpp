/* generate all prime numbers in [1, n], and store them in prime[] in ascending order. */
/* cnt stands for the number of primes generated. */
/* time complexity: O(n*loglogn) */
/* space compleity: O(n) */

int _visited[i] = {0};
int prime[MAX];
int cnt = 0;
void prime_table(int n){
    for(int i=2; i<=n; ++i){
        if(!visited[i]){
            prime[cnt++] = i;
            for (int j=i*i; j<=n; j+=i)
                _visited[j] = 1;
        }
    } 
}
