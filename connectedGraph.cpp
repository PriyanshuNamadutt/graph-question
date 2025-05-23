class disjointset {
    public:
    vector<int> rank , parent;
    
    disjointset( int n ) {
        rank.resize( n , 0 );
        parent.resize( n );
        for ( int i = 0; i < n; i++ ) {
            parent[i] = i;
        }
    }
    
    int findpar ( int u ) {
        if ( parent[u] == u ) return u;
        return parent[u] = findpar( parent[u] );
    }
    
    void unionByrank( int u , int v ) {
        int ult_u = findpar( u );
        int ult_v = findpar( v );
        
        if ( ult_u == ult_v ) return;
        if ( rank[ult_u] < rank[ult_v] ) parent[ult_u] = ult_v;
        else if ( rank[ult_u] > rank[ult_v] ) parent[ult_v] = ult_u;
        else {
            rank[ult_u]++;
            parent[ult_v] = ult_u;
        }
    }
};

class Solution {
  public:
    int Solve(int n, vector<vector<int>>& edge) {
        // code here
        
        if ( edge.size() < n-1 ) return -1;
        disjointset ds( n );
        int cnt = n;
        for ( int i = 0; i < edge.size(); i++ ) {
            int u = edge[i][0];
            int v = edge[i][1];
            
            if ( ds.findpar( u ) != ds.findpar( v ) ) {
                cnt--;
                ds.unionByrank( u , v );
            }
        }
        return cnt-1;
    }
};
