/* simple disjoint set using union-by-rank with path compression*/
/* time  complexity: O(m a(n)) for m operations where a(n)<=4 for n<(1e80)*/
/* spcae complexity: O(N) */
/* MAX_N: maximum number of disiojnt sets */
/* find : find the root of the element */
/* merge: the 'union' operation.
 *        called 'merge' because 'union' is a C++ keyword.
 */
class disjoint_set{
public:
    disjoint_set(){
        memset(_father, -1, sizeof(_father));
    }
    int find(int x){
        if(_father[x] < 0) return x;
        return _father[x] = find(_father[x]);
    }
    void merge(int x, int y){
        int a = find(x);
        int b = find(y);
        if(a == b) return;
        if(_father[b] < _father[a]){
            _father[a] = b;
        }
        else{
            _father[b] = a;
            if(_father[a] == _father[b]){
                --_father[a];
            }
        }
    }
private:
    int _father[MAX_N];
};
