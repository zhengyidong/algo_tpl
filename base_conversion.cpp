// convert a number n(in decimal) to base-radix
// return number of bits of n in base-radix and
// answer is stored in array 'ans' from least
// significant bit(LSB).
// note: you can use Integer.toString(n, base) to get the result string directly if use Java.
int ten_to_n(int n, int radix, int ans[20])
{
    for(int j = 0; j < 20; j++) ans[j] = 0;
    int num_bits = 1;
    ans[0] = n % radix;
    while((n /= radix) != 0) {
        ans[num_bits++] = n % radix;
    }
    return num_bits;
}
