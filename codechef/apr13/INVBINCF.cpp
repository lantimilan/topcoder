// given n and R
//
// find the smallest K in [0, 1, ..., 2^n -1]
// such that (2^n -1 choose K) mod 2^n = R
//
// if no such K, return -1
//
// n is 120
//
// Lucas's theorem can compute (n choose k) mod p
// an extension by Andrew Garville allows computing
// (n choose k) mod p^m
