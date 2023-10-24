#ifndef defs_hpp

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define defs_hpp
#define forn(i,i0,n) for(ll i = i0; i < (ll) n; i++)
#define ll int64_t
#define double long double
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL);

#endif
