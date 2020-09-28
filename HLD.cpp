void hld(int x,int p,int w)
{
    if(head[chain]==-1)
        head[chain]=x;

    id[x]=chain;
    pos[x]=tim;
    base[tim++]=w;

    int mx=-1;
    pii big={-1,-1};
    for(auto c:v[x])
    {
        if(c.F==p)
            continue;

        if(mx<sz[c.F])
        {
            mx=sz[c.F];
            big=c;
        }
    }

    if(big.F!=-1)
        hld(big.F,x,big.S);

    for(auto c:v[x])
    {
        if(c.F==p || c==big)
            continue;

        ++chain;
        hld(c.F,x,c.S);
    }
}
