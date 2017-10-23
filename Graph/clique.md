# 版本1
```c++
#define ctz(x) ((x)? __builtin_ctzll(x):64)

/*计算右边第一个1之后的0的个数
*最大计算为64,从右边起序号依次为0,1,2,...
*/
int ans,n;
ULL g[maxn];
//最大团
void BronKerbosch(ULL clique,ULL allow,ULL forbid){
    if(!allow && !forbid){
        ans = max(ans,__builtin_popcountll(clique));return;
    }
    if(!allow)return;
    int pivot = ctz(allow | forbid);//选择轴点
    ULL choose = allow & ~g[pivot];
    for(int u = ctz(choose) ; u<n ; u += ctz(choose>>(u+1))+1){
        BronKerbosch(clique|(1ULL<<u),allow&g[u],forbid&g[u]);
        allow ^=1ULL<<u;
        forbid|=1ULL<<u;
    }
}
```

# 版本２

```c++
const int MAX_V = 55;
bitset<MAX_V> g[MAX_V],clique,allow,forbid;


//暴力枚举
int ans,n;
void BronKerbosch(int sz,bitset<MAX_V> allow, bitset<MAX_V> forbid,int begin=0) {
    if(allow.none()&&forbid.none()){
        ans = max(ans,sz);
        return;
    }
    if(allow.none())return;
    int pivot = 0;
    for(int i=0 ; i<n ; ++i)
        if(allow[i]|forbid[i]){pivot = i;break;}
    bitset<MAX_V> choose = allow & (~g[pivot]);
    for(int u=begin ; u<n ; ++u){
        if(choose[u]){
            sz++;
            BronKerbosch(sz,allow&g[u],forbid&g[u],begin=0);
            sz--;
            allow.set(u,0);
            forbid.set(u);
        }
    }
}
```

# 版本３
```c++
std::vector<int> g[MAX_V];

int mat[maxn][maxn];
//暴力枚举
int ans = 0;
int n,m,s;
int cnt;
int Stack[maxn];
bool ok(int u){
    for(int i=0 ; i<cnt ; ++i)
        if(!mat[u][Stack[i]])return 0;
    return 1;
}
void dfs(int u,int idx){
    if(cnt ==s){ans++;return;}
    if(g[u].size()+cnt <s|| idx >=g[u].size())return;
    if(ok(g[u][idx])){
        Stack[cnt++] = g[u][idx];
        dfs(u,idx+1);
        cnt--;
    }
    dfs(u,idx+1);
}

int main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);

    int T;
    cin>>T;

    int allow[100];
    while (T--) {
        cin>>n>>m>>s;
        for(int i=0 ; i<n ; ++i)g[i].clear();
        ms(mat,0);
        for(int i=0 ; i<m ; ++i){
            int u,v;
            scanf("%d%d",&u,&v );
            u--;v--;
            if(u==v)continue;
            mat[u][v] = mat[v][u] =1;
            g[u].pb(v);
            g[v].pb(u);
        }
        ans =0;
        for(int i=0 ; i<n ; ++i){
            cnt =0;
            Stack[cnt++] = i;
            dfs(i,0);
            for(int j=0 ; j<n ; ++j){
                if(mat[i][j])mat[i][j]=mat[j][i] = 0;
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}

```
