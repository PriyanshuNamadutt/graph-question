class disjointset {
    public:
    vector<int> rank , parent;
    
    disjointset ( int n ) {
        rank.resize( n , 0 );
        parent.resize( n );
        for ( int i = 0; i < n; i++ ) {
            parent[i] = i;
        }
    }
    
    int findpar ( int node ) {
        if ( node == parent[node] ) return node;
        
        return parent[node] = findpar( parent[node] );
    }
    
    void unionByrank ( int u , int v ) {
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
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators) {
        // code here
        vector<vector<int>> vis(n , vector<int>(m,0) );
        int cnt = 0;
        
        vector<int> delr = {-1,0,1,0};
        vector<int> delc = {0,-1,0,1};
        
        disjointset ds( n*m );
        int k = operators.size();
        vector<int> ans( k );
        for ( int i = 0; i < k; i++ ) {
            int row = operators[i][0];
            int col = operators[i][1];
            
            if ( vis[row][col] ) {
                ans[i] = cnt;
                continue;
            }
            
            vis[row][col] = 1;
            cnt++;
            for ( int j = 0; j < 4; j++ ) {
                int nrow = row + delr[j];
                int ncol = col + delc[j];
                
                if ( nrow >= 0 && ncol >= 0 && nrow < n && ncol < m && vis[nrow][ncol] ) {
                    
                    if ( ds.findpar( nrow*m + ncol) != ds.findpar( row*m + col ) ) {
                        ds.unionByrank( row*m + col , nrow*m + ncol );
                        cnt--;
                    }
                }
            }
            
            ans[i] = cnt;
        }
        return ans;
    }
};
