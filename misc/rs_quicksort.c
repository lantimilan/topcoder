// =========================================================
// 
//       Filename:  rs_quicksort.c
// 
//    Description:  code demonstrates a bug in Sedgewick's
//    Algorithm in C, 2nd ed, page 326, Program 7.5
//    the last two for loops should be <= and >=
// 
//        Version:  1.0
//        Created:  01/08/2013 08:49:10 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/08/2013, LI YAN
// 
// =========================================================

#include <stdio.h>

typedef int Item;

#define less(A, B) ((A) < (B))
#define eq(A, B) (!less(A, B) && !less(B, A))
#define exch(A, B) { Item t = A; A = B; B = t; }

void print(int a[], int n)
{
    for (int i=0; i<n; ++i)
        printf("%d ", a[i]);
    putchar('\n');
}
void quicksort(Item a[], int l, int r)
{
    int i, j, k, p, q;
    Item v;

    printf("quicksort l %d r %d\n", l, r);
    if (r <= l) return;

    print(a, r-l+1);
    v = a[r]; i = l-1; j = r; p = l-1; q = r;
    for (;;) {
        while (less(a[++i], v)) ;
        while (less(v, a[--j]))
            if (j == l) break;
        if (i >= j) break;
        exch(a[i], a[j]);
        if (eq(a[i], v)) { p++; exch(a[p], a[i]); }
        if (eq(a[j], v)) { q--; exch(a[q], a[j]); }
        print(a, r-l+1);
    }
    printf("p %d q %d i %d j %d\n", p, q, i, j);
    exch(a[i], a[r]); print(a, r-l+1);
    j = i-1; i = i+1;
    printf("before eq, p %d q %d i %d j %d\n", p, q, i, j);
    for (k=l; k<=p; k++, j--) exch(a[k], a[j]);  // should here be k <= p?
    for (k=r-1; k>=q; k--, i++) exch(a[k], a[i]);  // same here, k>=q?
    printf("center eq, p %d q %d i %d j %d\n", p, q, i, j);
    print(a, r-l+1);
    quicksort(a, l, j);
    quicksort(a, i, r);
}

int main()
{
    int a[] = {15, 15, 15, 15, 10, 3, 10, 15, 15, 15, 15, 15, 15};
    int i, n;
    n = sizeof(a)/sizeof(a[0]);
    quicksort(a, 0, n-1);
    for (i=0; i<n; ++i)
        printf("%d ", a[i]);
    putchar('\n');
}
