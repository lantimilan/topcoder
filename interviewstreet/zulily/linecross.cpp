// =========================================================
// 
//       Filename:  linecross.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/16/2012 12:12:56 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/16/2012, LI YAN
// 
// =========================================================

typedef pair<int,int> pii;
// horizontal segments
typedef pair<pii, int> hori_t; // (xmin, xmax), y
typedef pair<pii, pii> vert_t; // (xval, index),(ymin, ymax)

set<pii> ytable; // yval, id

int N, Q;
vector<hori_t> segs;
vector<vert_t> vers;
vector<pii> ans; // (index, cross)

int main()
{
    scanf("%d", &N);
    int x,y,l;
    for(int i=0; i<N; ++i) { 
        scanf("%d%d%d", &x, &y, &l);
        segs.push_back(hori_t(pii(x,x+l), y));
    }
    scanf("%d", &Q);
    for(int i=0; i<Q; ++i) {
        scanf("%d%d%d", &x, &y, &l);
        vers.push_back(vert_t(pii(x,i), pii(y,y+l)));
    }
    sort(segs.begin(), segs.end());
    sort(vers.begin(), vers.end());
    int S=segs.size();
    int V=vers.size();
    int a, b, j;
    for(a=b=j=0; j<V; j++) {
        if (b<S && segs[b].first.first <= vers[j].first.first) {
            ytable.insert(pii(segs[b].second, b));
            b++;
        }
        else {
            while(a<S && segs[a].first.second < vers[j].first.first) {
                ytable.erase(pii(segs[a].second, a));
                a++;
            }
        }
    }
}

// don't know
