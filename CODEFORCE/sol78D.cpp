   1. #include <iostream>
   2. #include <sstream>
   3. #include <string>
   4. #include <vector>
   5. #include <deque>
   6. #include <queue>
   7. #include <set>
   8. #include <map>
   9. #include <algorithm>
  10. #include <functional>
  11. #include <utility>
  12. #include <cmath>
  13. #include <cstdlib>
  14. #include <ctime>
  15. #include <cstdio>
  16.

  17. using namespace std;
  18.

  19. #define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
  20. #define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
  21.

  22. typedef long long ll;
  23.

  24. ll dist(ll x, ll y){
  25.     return 3*x*x + 3*y*y + 3*x*y + 3*x + 3*y + 1;
  26. }
  27.

  28. int main(void){
  29.     ll ans = 0;
  30.    
  31.     ll D;
  32.     cin >> D;
  33.     D = D * D;
  34.    
  35.     if(dist(0,0) > D){
  36.         cout << 0 << endl;
  37.         return 0;
  38.     }
  39.    
  40.     ll x = 0, y = 0;
  41.     while(dist(x+1,y) <= D) x++;
  42.    
  43.     ll tmp = x;
  44.    
  45.     while(1){
  46.         while(dist(x,y+1) <= D) y++;
  47.         ans += y + 1;
  48.         x--;
  49.         if(x < 0) break;
  50.     }
  51.    
  52.     ans = (ans - 2*tmp - 1) * 6 + 6*tmp + 1;
  53.     cout << ans << endl;
  54.    
  55.     return 0;
  56. }
