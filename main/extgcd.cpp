/* find (x, y) pair that gcd(a, b) = a*x + b*y */
/* time  complexity: O(log(min(a, b))) */
/* space complexity: O(1) */
int extgcd(int a, int b, int & x, int & y){
    if (b == 0) { x=1; y=0; return a; }
    int d = extgcd(b, a % b, x, y);
    int t = x; x = y; y = t - a / b * y;
    return d;
}
