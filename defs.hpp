#ifndef defs_hpp
#define defs_hpp

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define forn(i,i0,n) for(ll i = i0; i < (ll) n; i++)
#define ll long long
#define double long double
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL);


using namespace std;

struct airplane_data{
    ll e,t,l;
    double g,h;
    vector<ll> times;
};
vector<ll> get_optimal_positions(vector<ll> positions,vector<airplane_data> airplanes);
double eval_function(vector<ll> &values,vector<airplane_data> &airplanes,ll = 0,ll = 1000);
vector<ll> gready_construction(vector<airplane_data> &airplanes);
vector<ll> get_order(vector<ll> ans); vector<ll> get_revserse_order(vector<ll> positions,vector<ll> values);

#endif
