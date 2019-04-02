#include<bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f
#define INF64 0x3f3f3f3f3f3f3f3f
#define ms(x,v) memset(x,(v),sizeof(x))

typedef long long LL;
typedef pair<int,int> PII;


const int MAXN = 250 +10;

int a[MAXN][MAXN];
int dist[MAXN][MAXN];
int r,c;

inline bool out_of_bound(int x,int y){
    return x <1 || x > r || y <1 || y > c;
}

int bfs(){
    const int dx[] = {-1,0,0,1};
    const int dy[] = {0,1,-1,0};
    queue<PII> Q;
    for(int i=1 ; i<=r ; ++i)
        for(int j=1 ; j<=c ; ++j)
            if(a[i][j])
            {
                dist[i][j] =0;
                Q.push(make_pair(i,j));
            } 
    int max_dist = 0;
    while(!Q.empty()){
        auto now = Q.front();
        Q.pop();
        max_dist = dist[now.first][now.second];
        for(int dir = 0 ; dir < 4 ;++ dir){
            int i = now.first + dx[dir];
            int j= now.second + dy[dir];
            if(!out_of_bound(i,j) && dist[i][j] == -1){
                dist[i][j] = max_dist + 1;
                Q.push(make_pair(i,j));
            }
        }
    }
    return max_dist;
}

bool ok(int mid){
    int x = -INF;
    int y = INF;
    int z =- INF;
    int w = INF;
    for(int i =1; i <=r ; ++i)
        for(int j=1 ; j<=c ; ++j)
            if(dist[i][j] >mid){
                x = max(x, i+j);
                y = min(y,i+j);
                z = max(z,i-j);
                w = min(w,i-j);
            }
    if(w == INF) return true;
    for(int i=1 ; i<=r ; ++i)
        for(int j=1 ; j<=c ; ++j)
            if(abs(x - (i+j)) <=mid &&
               abs(y - (i+j)) <=mid &&
               abs(z - (i-j)) <=mid &&
               abs(w - (i-j)) <=mid)
               return true;
    return false;
}

int main(){

    ios :: sync_with_stdio(0);
    cin.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    
    int T;
    cin >> T;
    for(int t =1 ; t <= T; ++t){
        ms(dist,-1);
        cin >> r >> c;
        for(int i=1 ; i<=r ; ++i){
            string s;
            cin >> s;
            for(int j=0 ; j< c ; ++j)
            {
                a[i][j+1] = (s[j] == '1');
            }
        }

        int hi = bfs();
        int ans = hi;
        int lo = 0;
        while(lo <= hi){
            int mid = (hi + lo) >> 1;
            if(ok(mid))hi = mid -1;
            else lo = mid+1;
        }
        ans = hi +1;
        cout << "Case #"<<t<<": "<<ans<<"\n";
    }
    return 0;
}
