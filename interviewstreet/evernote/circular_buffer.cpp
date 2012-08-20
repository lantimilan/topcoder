// =========================================================
// 
//       Filename:  circular_buffer.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/11/2012 09:24:47 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/11/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct buffer_t {
    int capacity;
    int size;
    int head, tail;
    vector<string> elems;

    buffer_t(int n) { capacity=n; size=0; head=0; tail=0; elems = vector<string>(n); }
    void append();
    void remove();
    void list();
};

void buffer_t::append()
{
    int n; cin >> n;
    for(int i=0; i<n; ++i) {
        cin >> elems[tail];
        tail = (tail+1) % capacity;
        if (size < capacity) {
            size++; 
        } else {
            head = (head+1) % capacity;
            assert(head == tail);
        }
    }
}

void buffer_t::remove()
{
    int n; cin >> n;
    assert(n <= size);
    head = (head + n) % capacity;
    size -= n;
}

void buffer_t::list()
{
    if (size<=0) return;
    for(int s=head, i=0; i<size; s=(s+1)%capacity, ++i) {
        cout << elems[s] << endl;;
    }
}

int main()
{
    int N; cin >> N;
    buffer_t buf(N);

    string cmd;
    while(cin >> cmd) {
        if (cmd[0] == 'Q') break;
        switch (cmd[0]) {
        case 'A': buf.append(); break;
        case 'R': buf.remove(); break;
        case 'L': buf.list(); break;
        default: assert(false);
        }
    }
}
