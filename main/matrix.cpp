/* a simple matrix implementation for integer elements. */
/* NOTE that the indexs of row and column start from 1. */
/* It's very easy to modify it to a 'double' version.   */
/*usage:
  1. It should be easy to use due to encapsulation.
  2. You can initialize the matrix to zero matrix or identity matrix by passing parameter 'opt'.

  NOTE that power() is not provided since power-and-mod is often the case for integer matrix. power()
  can be easily implemented by removing the 'mod' part of power_mod().
*/

class matrix{
    public:
        enum option{ZERO, IDENTITY};
        matrix(int row, int col, option opt=ZERO):_row(row), _col(col){
            memset(_m, 0, sizeof(_m));
            if(opt == IDENTITY)
                for(int i=1, len=std::min(_row,_col);i<=len; ++i) _m[i][i] = 1;
        }
        matrix(const matrix& mb){
            _row = mb.row();
            _col = mb.col();
            memcpy(_m, mb._m, sizeof(_m));
        }
        int* operator[](int i){
            return _m[i];
        }
        int tr() const{
            int ans = 0;
            for(int i=1, len=std::min(_row,_col); i<=len; ++i) ans += _m[i][i];
            return ans;
        }
        matrix operator*(const matrix& mb) const{
            int col_mb = mb.col();
            matrix ret(_row, col_mb);
            for(int i=1; i<=_row; ++i)
                for(int j=1; j<=col_mb; ++j)
                    for(int k=1; k<=_col; ++k)
                        ret._m[i][j] += _m[i][k] * mb._m[k][j];
            return ret;
        }
        matrix operator%(int mod) const{
            matrix ret = *this;
            for(int i=1; i<=_row; ++i)
                for(int j=1; j<=_col; ++j){
                    while(ret[i][j] < 0) ret[i][j] += mod;
                    ret[i][j] %= mod;
                }
            return ret;
        }
        matrix power_mod(int b, int n){
            matrix ans(_row, _col, IDENTITY);
            matrix a = *this;
            a = a % n;
            while(b > 0){
                if(b & 1) ans = (ans * a) % n;
                b >>= 1;
                a = (a * a) % n;
            }
            return ans;
        }
        int col() const{ return _col; }
        int row() const{ return _row; }
    private:
        int _m[MAX_N][MAX_N];
        int _row;
        int _col;
};

/* a simple circulant matrix implementation for integer elements. */
/* NOTE that the indexs of row and column start from 1. */
/* There is no much difference between these two versions. */
/* However, this special version saves time and space. */
class circulant_matrix{
public:
    enum option{ZERO, IDENTITY};
    int order()const {return _order;}
    circulant_matrix(int order, option opt=ZERO):_order(order){
        memset(_m, 0, sizeof(_m));
        if(opt == IDENTITY) _m[1] = 1;
    }
    circulant_matrix(const circulant_matrix& mb){
        _order = mb.order();
        memcpy(_m, mb._m, sizeof(_m));
    }
    LL& operator[](int index){
        return _m[index];
    }
    circulant_matrix operator*(const circulant_matrix& mb) const{
        circulant_matrix ret(_order);
        for(int i=1; i<=_order; ++i)
            for(int j=1; j<=_order; ++j)
                ret._m[i] += _m[j] * mb._m[(i-j+_order)%_order + 1];
        return ret;
    }
    circulant_matrix operator%(int mod) const{
        circulant_matrix ret = *this;
        for(int i=1; i<=_order; ++i){
                while(ret[i] < 0) ret[i] += mod;
                ret[i] %= mod;
        }
        return ret;
    }
    circulant_matrix power_mod(int b, int n){
        circulant_matrix ans(_order, IDENTITY);
        circulant_matrix a = *this;
        a = a % n;
        while(b > 0){
            if(b & 1) ans = (ans * a) % n;
            b >>= 1;
            a = (a * a) % n;
        }
        return ans;
    }

private:
    LL _m[501];
    int _order;
};
