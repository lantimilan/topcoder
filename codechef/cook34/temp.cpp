using namespace std;
int in() {
    int r=0,c;
    for(c=getchar_unlocked(); c<=32; c=getchar_unlocked());
    if(c=='-') return -in();
    for(; c>32; r=(r<<1)+(r<<3)+c-'0',c=getchar_unlocked());
    return r;
}
typedef long long ll;

#define MAXN 10020
int prime[MAXN];  // prime[j] is the last prime that divides j
int sz;
int primes[MAXN];
int inv[MAXN];
void criba() {
    for(int i=0; i<MAXN; i++) {
        prime[i]=i;
    }
    sz =0;
    for(int i=2; i<MAXN; i++) {
        if(prime[i]==i) {
            inv[i] = sz;
            primes[sz++] = i;
            if(i<MAXN/i)
                for(int j=i*i; j<MAXN; j+=i) {
                    prime[j]=i;
                }
        }
    }
}

int a[1010];
ll can[10101];

void solve() {
    memset(can,0,sizeof can);
    int N = in();
    int i,j,k;
    for(i=0; i<N; i++) a[i] = in();
    ll ans = 0;
    for(i=0; i<N; i++) {
        int d = a[i];
        vector<int> fact;  // fact is vector of prime factors
        // notice that fact has size at most 5
        // because 2,3,5,7,11,13 = 30030 > 10000 = MAXN
        while(d!=1) {
            int e = prime[d];
            fact.push_back(e);
            while(d%e==0) d/=e;
        }
        ans += ((1LL<<i)-1);
//cerr << i << ' ' << ans << endl ;
        int m = fact.size();  // m is at most 5
        for(j=1; j<(1<<m); j++) {
            int por= __builtin_popcount(j)&1 ? -1 : 1;
            int num = 1;
            for(k=0; k<m; k++) if(j&(1<<k)) {
                    num*=fact[k];
                }

            ans += por * ((1LL<<can[num])-1);
            can[num]++;
        }
//cerr << i << ' ' << ans << endl ;
    }
    cout << ans << endl;
}

int main() {
    criba();
    for(int i=0,T=in(); i<T; i++)
        solve();
}

