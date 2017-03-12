
int st[MAX_V][32];
//返回下标的RMQ；
void  RMQ_init(const int *A,int n)
{
  for(int i=0 ; i<n ; ++i)st[i][0] = i;

  for(int j = 1 ; (1<<j)<=n ; ++j)
    for(int i =0 ; i+(1<<j)-1<n ; ++i)
    if(A[st[i][j-1]]<A[st[i+1<<(j-1)][j-1]])
      st[i][j] = st[i][j-1];
    else st[i][j] = st[i+1<<(j-1)][j-1];
}
//最小值的下标
int query(const int *A,int L,int R){
  if(R<L)return -1;
  int k=0;
  while(1<<(k+1)<=R-L+1)k++;
  if(A[st[L][k]]<A[st[R-(1<<k)+1][k]])
    return st[L][k];
  else return st[R-(1<<k)+1][k];
}
//LCA
std::vector<int> G[MAX_V];

struct LCA{
  int root;
  int vs[MAX_V<<1];//访问数组
  int depth[MAX_V<<1]//深度数组
  int pos[MAX_V];//位置数组

  void dfs(int v,int p,int d,int& k){
    pos[v] = k;
    vs[k] = v;
    depth[k++] = d;
    for(int i=0 ; i<G[v].size() ; ++i)
      if(G[v][i] !=p){
        dfs(G[v][i],v,d+1,k);
        vs[k] = v;//回退
        depth[k++] = d;
      }
  }

  //预处理
  void init(int V,int r){
    int k=0 ;
    root = r;
    dfs(root,-1,0,k);
    RMQ_init(depth,2*V-1);
  }

  int lca(int u,int v){
    if(pos[u]>pos[v])swap(u,v);
    return vs[query(depth,pos[u],pos[v])];
  }
};
