#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5;
int lg[MAX];

int table[MAX][25];

void build(vector<int>& a);
int query(int l, int r);

class SparseTable{
public:
    
    SparseTable(vector<int>&a){
        build(a);
    }

    int get_sum(int l,int r){
        return query(l,r);
    }
};
// [l, l+(1<<w)-1]
void build(vector<int>&a){
    int n = a.size();
    for(int l=n-1;l>=0;l--){
        for(int w=0;w<25;w++){
            int r = l+(1<<w);
            if(r>n)break;
            if(w==0){
                table[l][w] = a[l];
            }else{
                table[l][w] = table[l][w-1]+table[l+(1<<(w-1))][w-1];
            }
        }
    }
    return;
}
int query(int l,int r){
    
    int rem = r-l+1;
  
    int sum = 0;
    while(rem>0){
        int power = lg[rem];
        sum +=table[l][power];
        l+=(1<<power);
        rem-=(1<<power);
    }
    return sum;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
     lg[1] = 0;
     lg[0] = 0;
     for(int i=2;i<MAX;i++){
        lg[i] = 1+lg[i/2];
     }
     int p,q;
     cin>>p>>q;
     vector<int>a = {1,3,5,7,9,11};
     SparseTable st(a);
     cout<<"Sum of range: "<< st.get_sum(p-1,q-1)<<endl;
    return 0;
}