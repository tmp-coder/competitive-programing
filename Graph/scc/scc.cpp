

std::vector<int> G[MAX_V];
std::vector<int> rG[MAX_V];
bool vis[MAX_V];
int scc[MAX_V];
std::vector<int> vs;//访问结束时间栈
void add_edge(int u,int v){
  G[u].push_back(v);
  G[v].push_back(u);
}
void dfs(int u) {
  vis[u] = true;
  for(int i=0 ; i<G[u].size() ;++i)
    if(!vis[G[u][i]])dfs(G[u][i]);
  vs.push_back(u);
}

void rdfs(int u,int scc_cnt) {
  vis[u] = true;
  scc[u] = scc_cnt;
  for(int i=0 ; i<rG[u].size() ; ++i)
    if(!vis[rG[u][i]])rdfs(rG[u][i]);
}

int Kosaraju(int nv){
  int scc_cnt = 0;
  memset(vis,false,sizeof(vis));
  vs.clear();
  for(int i=0 ; i<v ; ++i)
    if(!vis[i])dfs(i);
  memset(vis,false,sizeof(vis));
  for(int i= vs.size()-1 ; i>=0 ; --i)
    if(!vis[vs[i]])rdfs(vs[i],++scc_cnt);
  return scc_cnt;
}
