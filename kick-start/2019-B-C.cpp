#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)
#define INF 0x3f3f3f3f

typedef long long LL;


const int MAXN = 100000 + 3;

int a[MAXN];
int S,n;

struct SegTree{
    int tree[MAXN<<2],lazy[MAXN<<2];
    void clear(){
        ms(tree,0);
        ms(lazy,0);
    }
    void update(int val,int ul,int ur,int node=1,int l=1,int r=n){
        if(ul > r || ur < l)return;
        if(ul<=l && r <= ur){// contained
            lazy[node] += val;
            tree[node] += val;
            return;
        }
        int lc = node <<1, rc = node <<1 |1;
        int mid = (l+r) >>1;
        update(val,ul,ur,lc,l,mid);
        update(val,ul,ur,rc,mid+1,r);
        tree[node] = max(tree[lc],tree[rc]) + lazy[node];
    }

    int Max(int ul,int ur,int node=1,int l=1,int r=n){
        
        if(ul>r || ur <l)return -INF;
        if(ul <=l && r <=ur) return tree[node];
        int mid = (l+r) >>1;
        return max(Max(ul,ur,node<<1,l,mid),Max(ul,ur,node<<1|1,mid+1,r));
    }
};

SegTree seg;

int main(int argc, char const *argv[])
{   
    ios :: sync_with_stdio(0);
    cin.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    int T;
    cin >> T;

    for(int t =1;  t <= T ; ++t)
    {
        
        cin >>n >> S;
        vector<int> pos[MAXN];
        int ptr[MAXN];

        for(int i=1 ; i<=n ; ++i){
            cin >> a[i];
            pos[a[i]].push_back(i);
        }
        for(int i=1 ; i <MAXN ; ++i)ptr[i] = pos[i].size()-1; // current access pos

        seg.clear();
        int ans =0;
        for(int l = n ; l >0 ; --l){
            seg.update(1,l,n);

            int cur = a[l];
            if(ptr[cur] + S <= pos[cur].size()-1){
                int st = pos[cur][ptr[cur]+S];
                seg.update(-(S+1),st,n);
            }
            if(ptr[cur] + S < pos[cur].size() -1){
                int st = pos[cur][ptr[cur] +S +1];
                seg.update(S,st,n);
            }
            ptr[cur]--;
            ans = max(ans,seg.Max(1,n));
        }

        cout << "Case #"<<t << ": " << ans << "\n";
    }

    return 0;
}
