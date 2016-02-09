/* merge sort including calculating number of inverse pairs. */
/* time  complexity: O(NlogN) */
/* space complexity: O(N) */
/* usage             :[optional: num_invrese_pairs=0]merge_sort(0, N) */
/* a[0..N-1]         :original array */
/* c[0..N-1]         :augxiliary array */
/* num_inverse_pairs :number of inverse pairs in original array */
/*                    init to 0 if use it. */
void merge_sort(int l, int r){
    int mid, i, j, tmp;
    if(r > l + 1){
        mid = (l + r) / 2;
        merge_sort(l, mid);
        merge_sort(mid, r);
        tmp = l;
        for(i=l, j=mid; i<mid&&j<r; ){
            if(a[i] > a[j]){
                c[tmp++] = a[j++];
                num_inverse_pairs += mid - i; //
            }
            else c[tmp++] = a[i++];
        }
        if(j < r) for( ;j<r; ++j) c[tmp++] = a[j];
        else for( ;i<mid; ++i) c[tmp++] = a[i];
        for (i=l; i<r; ++i) a[i] = c[i];
    }
}
