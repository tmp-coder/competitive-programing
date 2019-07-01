#include<bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int T;
    cin >> T;
    int n,q;
    for (size_t t = 1; t <= T; t++)
    {
        cin >> n >> q;
        string s;
        cin >>s;
        vector<int> ch[26];
        for (size_t i = 0; i < s.size(); i++)
        {
            ch[s[i]-'A'].push_back(i+1);
        }
        int y =0;
        while (q --)
        {
            int l,r;
            cin >>l >> r;
            int odd =0;
            for(int i=0 ; i< 26 ; ++i)
            {
                int cnt = upper_bound(ch[i].begin(),ch[i].end(),r) - lower_bound(ch[i].begin(),ch[i].end(),l);
                // cout << (char)('A'+i) << " : " <<cnt << "\n"; 
                if(cnt &1)odd ++;
            }
            y += (odd <=1);
        }

        cout << "Case #"<<t << ": "<<y << "\n";
    }
    
        
    return 0;
}
