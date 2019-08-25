namespace Prime{
    #define random(a,b) (rand() % ((b) -(a)) +(a))
    LL power_mod(LL x,LL n,LL mod){
        LL ret =1;
        while(n){
            if(n & 1) ret = x * ret % mod;
            x = x * x % mod;
            n >>=1;
        }
        return ret;
    }
    LL mulmod(LL x,LL y,LL n){ // x ,y <= 10^9
        return x * y % n;
    }
    bool witness(LL a,LL n,LL u,LL t){
        LL x0 = power_mod(a,u,n),x1;
        for(int i=1 ;i<=t ; ++i){
            x1 = mulmod(x0,x0,n);
            if(x1==1 && x0!=1 && x0!=n-1)
                return false;
            x0 = x1;
        }
        if(x1 !=1)return false;
        return true;
    }

    bool miller_rabin(LL n, int times = 20){
        if(n < 3) return n==2;
        if(!(n&1))return false;
        LL u = n-1,t =0;
        while (u%2==0) {
            t++;u>>=1;
        }
        while (times--) {
            LL a = random(1,n-1);
            //if(a == 0)std::cout << a << " "<<n<< " "<<u<<" " << t<<'\n';
            if(!witness(a,n,u,t))return false;
        }
        return true;
    }
};
