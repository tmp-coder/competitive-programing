// discretize a vector
// 
// example:
// 1,10,3,5 -> 0,3,1,2
// NOTE: re-write parameter, not functional
// return : number of non-duplicated elements
int discretization(vector<int> & raw){
  
    // discretization
    vector<int> id = raw;
    sort(id.begin(),id.end());
    auto it_end = unique(id.begin() , id.end());
    for(int i=0 ; i<raw.size() ; ++i)
        raw[i] = lower_bound(id.begin(),it_end,raw[i]) - id.begin();
    
    return it_end - id.begin();
}
