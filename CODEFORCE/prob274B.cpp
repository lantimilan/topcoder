// prob274B.cpp
//
// 1. There is always a solution.
// proof by induction, first work out T[1..n-1], then work on T[n]
// 2. Operations can be swapped, that is, order of operations do not matter
// The end result is the same if we perform a set of operations with any
// permutation of order.
// 3. As a consequence, there is one leaf node (root is node[1]) that is
// changed only  once
