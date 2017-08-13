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
