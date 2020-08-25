#include<bits/stdc++.h>
#define ll long long int
using namespace std;
ll k=0;
ll result=0;
struct node{
    ll n1;
    ll n2;
    ll w;
};
ll min (ll a, ll b){
    if(a<b)return a;
    else return b;
}
vector<node>e;
vector<node>a;
ll siz[5005]={0};
ll par[5005]={0};
ll root(ll node){
    if(par[node]==node) return node;
    else return root(par[node]);
}
ll connect(ll a, ll b){
    ll A=root(a);
    ll B=root(b);
    if(A==B) return 0;
    if(siz[A]>siz[B]){
        par[B]=A;
        siz[A]=siz[A]+siz[B];
        return 1;
    }
    else{
        par[A]=B;
        siz[B]=siz[A]+siz[B];
        return 1;
    }
}

bool compC(const node &e1, const node &e2){
    if(e1.w==e2.w) return min(e1.n1,e1.n2) < min(e2.n1,e2.n2);
    return e1.w < e2.w;
}
ll kruskal(ll n, ll g){
    printf("%lld\n",g);
    result=0;
    ll ans=0;
    ll i=0;
    ll l=0;
    ll len=e.size();
    for(ll j=0;j<5005;j++){
        par[j]=j;
        siz[j]=1;
    }
    a.clear();
    for(ll j=0;j<len;j++){
            a.push_back({e[j].n1,e[j].n2,e[j].w});
    }
    for(ll j=0;j<len;j++){
        if(a[j].n1==1 || a[j].n2==1) a[j].w+=g;
    }
    sort(a.begin(),a.end(),compC);
    i=0;
    while((l<n-1)&&(i<len)){
            if(connect(a[i].n1,a[i].n2)){
                l++;
                result+=a[i].w;
                if(a[i].n1==1 || a[i].n2==1)ans++;
            }
            i++;
    }
    if(l!=n-1) {printf("-1\n"); exit (0);}
    printf("connections are %lld\n",ans);
    return ans;
}
int main(){
    ll n,m,u,v,w,res,conn;
    scanf("%lld %lld %lld",&n,&m,&k);
    while(m--){
        scanf("%lld %lld %lld",&u,&v,&w);
        e.push_back({u,v,w});
    }
//////////////////////////
// binary serach
    ll l=-100000;
    ll r=100000;
    res = -100001;
    ll g;
    while(l<=r){
        g=l+(r-l)/2;
        conn = kruskal(n,g);
        if(k<=conn) {l=g+1;res=g;}
        else {r=g-1;}
    }
///////////////////////////
// the case when tree is not formed at binary search:
    if(res < -100000){
        printf("-1\n");
        return 0;
    }

////////////////////////////////////
// last kruskal to see if required tree is possible

    result=0;
    ll ans=0;
    ll i=0;
     l=0;
    ll len=e.size();
    for(ll j=0;j<5005;j++){
        par[j]=j;
        siz[j]=1;
    }

    a.clear();
    for(ll j=0;j<len;j++){
            a.push_back({e[j].n1,e[j].n2,e[j].w});
    }
    for(ll j=0;j<len;j++){
        if(a[j].n1==1 || a[j].n2==1) a[j].w+=res;
    }
    sort(a.begin(),a.end(),compC);
    i=0;
    while((l<n-1)&&(i<len)){
        if(a[i].n1==1 || a[i].n2==1){
            if(ans<k && connect(a[i].n1,a[i].n2)){
                l++;
                result+=a[i].w;
                ans++;
            }
        }
        else if(connect(a[i].n1,a[i].n2)){
            l++;
            result+=a[i].w;
        }
        i++;
    }
    // tree not possible
    if(l!=n-1) {printf("-1\n"); return 0;}
    // tree possible
    printf("%lld\n",result-k*res);
    return 0;
}