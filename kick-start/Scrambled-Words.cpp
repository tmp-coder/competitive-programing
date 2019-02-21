#include<bits/stdc++.h>

using namespace std;

const int MAX_CHARS = 26;

typedef long long LL;
struct Key{
    char first,last;
    array<int,MAX_CHARS> freq;

    Key(const string& s){
        freq.fill(0);
        first = s.front();
        last = s.back();
        for(auto l : s)freq[l-'a']++;
        
    }
    bool operator==(const Key& o)const{
        return (first == o.first && last == o.last &&
                 freq == o.freq);
    }
};

namespace std{
    template<>
    struct hash<Key>{
        size_t operator()(const Key& k)const{
            size_t ret = 17,seed = 31;
            ret = ret * seed + k.first;
            ret = ret * seed + k.last;
            for(auto l : k.freq)ret = ret * seed + l;
            return ret;
        }
    };
}
set<size_t> lengths;
unordered_map<Key,int>  dict;    

void clear(){
    lengths.clear();
    dict.clear();
}

int solve(const vector<string> & words,const string & text){
    clear();

    for_each(words.begin(),words.end(),[](const string & s){
        lengths.insert(s.size());
        dict[Key(s)]++;
        });

    int ret =0;
    for(auto l : lengths){
        if(l > text.size())continue;
        Key k(text.substr(0,l-1));
        // k.len = l;
        for(int i=l-1 ;i < text.size() ;++i){
            k.first = text[i - l +1];
            k.last = text[i];
            k.freq[k.last-'a']++;

            auto it = dict.find(k);
            if(it != dict.end()){
                ret+=it->second;
                dict.erase(it);
            }

            k.freq[k.first-'a']--;
        }
    }
    return ret;
}

int main() {
    int T = 0;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int L = 0;
        cin >> L;
        vector<string> dictionary(L);
        for (string &word : dictionary) cin >> word;
        char S1 = 0, S2 = 0;
        int N = 0, A = 0, B = 0, C = 0, D = 0;
        cin >> S1 >> S2 >> N >> A >> B >> C >> D;
        vector<int> X(N);
        X[0] = S1;
        X[1] = S2;
        for (int i = 2; i < N; ++i) X[i] = ((long long)A*X[i - 1] + (long long)B*X[i - 2] + C)%D;
        string S;
        S.resize(N);
        S[0] = S1;
        S[1] = S2;
        for (int i = 2; i < N; ++i) S[i] = char('a' + X[i]%26);
        cout << "Case #" << t << ": " << solve(dictionary, S) << endl;
     }
}