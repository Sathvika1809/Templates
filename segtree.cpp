#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define py cout<<"YES"<<'\n'
#define pn cout<<"NO"<<'\n'

#define ll long long
#define eb emplace_back
#define sz 2e5+5

struct SegTree{
    int n;
    vector<ll>t;

    SegTree(int n):n(n),t(4*n){}

    void build(int node,int l,int r,vector<int>&a){
        if(l==r){
            t[node] = a[l];
            return;
        }
        int mid = l+(r-l)/2;
        build(node*2,l,mid,a);
        build(node*2+1,mid+1,r,a);

        t[node] = t[node*2 ] + t[node*2 +1];
    }

    ll query(int node, int l,int r,int p,int q){
        if(q<l ||r<p)return 0;
        if(p<=l && r<=q){
            return t[node];
        }
        int mid = l+(r-l)/2;
        return query(node*2 , l,mid,p,q)+
        query(node*2+1,mid+1,r,p,q);
    }
    void update(int node,int l,int r,int idx,int val){
        if(l==r){
            t[node]=val;
            return;
        }
        int mid = l+(r-l)/2;
        if(idx<=mid){
            update(node*2,l,mid,idx,val);
        }else{
            update(node*2+1,mid+1,r,idx,val);
        }
        t[node] = t[node*2]+t[node*2 + 1];
    }
};

signed main(){
     ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n=7;
    
    SegTree st(n);
    vector<int>a = {1,3,5,7,9,11,13};
    st.build(1,0,n-1,a);
    cout<<"Sum of Range: "<<st.query(1,0,n-1,1,4)<<'\n';
    st.update(1,0,n-1,2,6);
    cout<<"Sum of Range: "<<st.query(1,0,n-1,1,4)<<'\n';

    return 0;
}