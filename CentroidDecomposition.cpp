int nodes = 0;
vector<int> graph[MAXN];
int subtree[MAXN], parent[MAXN];
 
int dfs1(int node, int par){
    subtree[node] = 1;
    nodes++;
    for(auto u : graph[node])
        if(u != par)
            subtree[node] += dfs1(u, node);
    return subtree[node];
}
 
int dfs2(int node, int par){
    for(auto u : graph[node])
        if(u != par and subtree[u] > nodes/2)
            return dfs2(u, node);
    return node;
}
 
void decompose(int node, int par){
    nodes = 0;
    dfs1(node, node);
    int centroid = dfs2(node, node);
    if(par == -1)
        par = centroid;
    parent[centroid] = par;
    for(auto u : graph[centroid]){
        graph[u].erase(find(all(graph[u]), centroid));
        decompose(u, centroid);
    }
    graph[centroid].clear();
}