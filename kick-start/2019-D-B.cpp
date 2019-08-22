#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)
#define INF 0x3f3f3f3f

typedef long long LL;
typedef pair<int,int> PII;

const int MAXN = 2e5 +10;

struct Node{
    int cur,dir,ans;
    vector<int> ids;
};


void solve(){
    int N,G,M;
    cin >> N >> G>>M;
    vector<vector<int> > guests(2*N);

    for(int i=0 ; i< G; ++i){
        int s;
        char x;
        cin >> s>>x;
        s--;// map to [0,N)
        int dir = x == 'C' ? 1 : -1;
        s = (s + dir * (M%N) +N) % N;
        int idx = (s<<1) + (dir==1);
        guests[idx].push_back(i);
    }

    vector<Node> gg;
    for(int i=0 ; i<guests.size() ; ++i){
        if(guests[i].empty())continue;
        Node tmp = {
            i>>1,
            i&1 ? -1 : 1, // anti-dir
            0,
            guests[i],
        };
        gg.push_back(tmp);
    }
    vector<int> timep(N,-1);
    int not_vis = N;
    if(M > N) M = N;

    vector<bool> vis(2*N,false);

    set<int> unseen;
    for(int i=0 ; i< gg.size() ; ++i)unseen.insert(i);
    for(int time = M ; time >= 0 && not_vis>0 ; --time)
    {
        vector<int >del;
        for(auto i : unseen){
            int status = (gg[i].cur << 1) + (gg[i].dir==1);
            if(vis[status]){
                del.push_back(i);
                continue;
            }else vis[status] =true;
            int & cur = gg[i].cur;
            if(timep[cur]<time){
                not_vis--;
                timep[cur] = time;
            }//first access
            if(timep[cur] <=time){
                gg[i].ans ++;
            }
            gg[i].cur= (cur + gg[i].dir + N) % N;
        }
        for(auto e : del)unseen.erase(e);
    }
    vector<int> ans(G);
    for(auto e: gg){
        for(auto id : e.ids)
            ans[id] = e.ans;
    }
    for(int i=0 ; i < ans.size(); ++i)
            cout << " " << ans[i];
    
}

int main(int argc, char const *argv[])
{   
    
    ios :: sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    int T;
    cin >> T;
    
    for(int kase =1;  kase <= T ; ++kase)
    {   
        cout << "Case #"<<kase << ":";

        solve();
        cout << '\n';
    }

    return 0;
}
