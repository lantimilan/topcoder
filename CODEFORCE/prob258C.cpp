// find seq such that max is lcm
//
// a[i] <= 10^5, so can get all divisors of each 1 to 10^5
// this is only 10^7.5
//
// for each valid seq, one needs to be lcm, the rest can be
// any divisor (including lcm itself)
// this is all k^n minus (k-1)^n, where k is number of divisors of x
//
// n is 10^5
// order of elements is no interest, can sort or count number of occurrence
// of each val
