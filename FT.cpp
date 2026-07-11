#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define py cout<<"YES"<<'\n'
#define pn cout<<"NO"<<'\n'
#define int long long int
#define ll long long
#define eb emplace_back
#define sz 2e5+5

struct FT{
    int n;
    vector<ll> t;
    FT(int n):n(n),t(n+1) {}
    void add(int i, ll v){
        for(;i<=n;i+=(i&-i)){
            t[i]+=v;
        }
    }
    ll sum(int i){
        ll r=0;
        for(;i>=0;i-=(i&-i)){
            r+=t[i];
        }
        return r;
    }
    ll query(int l,int r){
        return sum(r)-sum(l-1);
    }
    int kth(ll k){
        int p = 0;
        for(int b=1<<__lg(n);b;b>>=1){
            if(p+b <= n && t[p+b]<k){
                k-=t[p+=b];
            }
        }
        return p+1;
    }
};