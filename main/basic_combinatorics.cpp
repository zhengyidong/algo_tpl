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

// sum of 1^m+2^m+...+n^m
// use first Bernoulli number
// invalid if m < 1.
// TODO(zyidong.zheng@gmail.com): make it valid when m=0
double sum_of_power(int m, int n, double B[]){
    if(n == 0) return 0;
    double sum = 0;
    for(int i=0; i<=m; ++i){
        sum += C(m + 1, i) * B[i] * pow(n+1, m+1-i);
    }
    return sum /= (m + 1);
}

// generate Bernoulli number from 0 to n
// using recursive defination.
// set optional argument 'first_kind' false if
// need second Bernoulli number.
void generate_B(double B[], int n, bool first_kind=true){
    B[0] = 1;
    for(int i=1; i<=n; ++i){
        B[i] = 0;
        for(int j=0; j<i; ++j){
            B[i] -= C(i+1, j) * B[j];
        }
        B[i] /= (i + 1);
    }
    if(!first_kind) B[1] = -B[1];
}
