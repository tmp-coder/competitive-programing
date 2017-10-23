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
bitset<MAX_V> g[MAX_V];
void BronKerbosch(int sz,bitset<MAX_V> allow, bitset<MAX_V> forbid,int begin=0) {
    if(sz==s){//特定个数
        ans++;
    }
    if(allow.none())return;
    for(int u=begin ; u<n ; ++u){
        if(allow[u]){
            sz++;
            BronKerbosch(sz,allow&g[u],forbid&g[u],begin=u);
            sz--;
            allow.set(u,0);
            forbid.set(u);
        }
    }
}
```
