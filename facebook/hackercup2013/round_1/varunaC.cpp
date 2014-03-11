#include <vector>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#define PRINT(x) cout << "DEBUG " << #x << " = " << x <<  endl;

#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define mp make_pair
#define fr(i, n) for(i = 0; i < (n); i++)
#define frr(i, n) for(int i = 0; i < (n); i++)
#define _cl(x) memset(x, 0, sizeof(x))
#define _rs(x) memset(x, -1, sizeof(x))

typedef vector<int> VI;
typedef pair<int, int> PII;
typedef istringstream ISS;
typedef ostringstream OSS;
typedef long long ll;

const int MAX = 41000;

int W, H, P, Q, N;
int x[1100100];
int y[1100100];
bool a[MAX][MAX];
int row[MAX];

void read(ifstream &fin) {
 int A, B, C, D, X, Y;

 fin >> W >> H >> P >> Q >> N >> X >> Y >> A >> B >> C >> D;

 x[0] = X, y[0] = Y;

 for(int i = 1; i < N; ++i) {
  x[i] = (x[i - 1] * A + y[i - 1] * B + 1) % W;
  y[i] = (x[i - 1] * C + y[i - 1] * D + 1) % H;
 }
}

inline void addRow(int r, int inc) {
 frr(c, W)
  if(a[r][c])
   row[c] += inc;
}

void proc(ofstream &fout) {
 _cl(a);
 _cl(row);

 frr(i, N)
  a[y[i]][x[i]] = true;

 ll res = 0;

 for(int r = H - 1, tr = H - 1 + Q; r >= 0; --r, --tr) {
  addRow(r, +1);
  if(tr < H)
   addRow(tr, -1);

  if(r + Q > H) continue;

  for(int c = W - 1, tc = W - P; c >= 0; --c) {
   if(row[c] > 0)
    tc = c - P;
   if(tc >= c)
    res++;
  }
 }

 fout << res << endl;
}

int main() {
 int i;
 int NT;

 ifstream fin("in");
 ofstream fout("out");
 string ln;

 getline(fin, ln);
 istringstream is(ln);
 is >> NT;

 fr(i, NT)
 {
  read(fin);
  fout << "Case #" << i + 1 << ": ";
  cout << "Case #" << i + 1 << endl;
  proc(fout);
 }

 return 0;
}
