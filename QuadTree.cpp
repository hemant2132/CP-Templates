/*
    submission for: https://www.spoj.com/problems/DQUERY/
*/

#include<bits/stdc++.h>
using namespace std;

#define inf 300003

struct quad_tree
{
    // child[0]=1st quadant, child[1]=2nd quadant so on
    int sum,child[4];
    quad_tree()
    {
        sum=0;
        child[0]=child[1]=child[2]=child[3]=-1;
    }
}nodes[1000000];
int cnt=1;

void insert_point(int node, int lx, int rx, int ly, int ry,int x, int y, int v)
{
    if(lx==rx and lx==x and ly==ry and ly==y)
    {
        nodes[node].sum=v;
        return;
    }
    int mx=(lx+rx)/2,my=(ly+ry)/2;
    if(x<=mx and y<=my)
    {
        if(nodes[node].child[2]<0)
        {
            nodes[node].child[2]=cnt++;
        }
        insert_point(nodes[node].child[2],lx,mx,ly,my,x,y,v);
    }
    else if(y<=my)
    {
        if(nodes[node].child[3]<0)
        {
            nodes[node].child[3]=cnt++;
        }
        insert_point(nodes[node].child[3],mx+1,rx,ly,my,x,y,v);        
    }
    else if(x<=mx)
    {
        if(nodes[node].child[1]<0)
        {
            nodes[node].child[1]=cnt++;
        }
        insert_point(nodes[node].child[1],lx,mx,my+1,ry,x,y,v);        
    }
    else
    {
        if(nodes[node].child[0]<0)
        {
            nodes[node].child[0]=cnt++;
        }
        insert_point(nodes[node].child[0],mx+1,rx,my+1,ry,x,y,v);
    }
    nodes[node].sum=0;
    for(int i=0;i<4;i++)
    {
        if(nodes[node].child[i]>=0)
        {
            nodes[node].sum+=nodes[nodes[node].child[i]].sum;
        }
    }
}
int query(int node, int lx, int rx, int ly, int ry,int x1, int x2, int y1, int y2)
{
    if(node==-1)
        return 0;
    if(!(lx<=x1 and x1<=x2 and x2<=rx and ly<=y1 and y1<=y2 and y2<=ry))
        return 0;
    if(lx==x1 and rx==x2 and ly==y1 and ry==y2)
    {
        return nodes[node].sum;
    }
    int mx=(lx+rx)/2,my=(ly+ry)/2,ans=0;
    ans+=query(nodes[node].child[2],lx,mx,ly,my,x1,min(mx,x2),y1,min(my,y2));
    ans+=query(nodes[node].child[3],mx+1,rx,ly,my,max(x1,mx+1),x2,y1,min(my,y2));
    ans+=query(nodes[node].child[1],lx,mx,my+1,ry,x1,min(mx,x2),max(my+1,y1),y2); 
    ans+=query(nodes[node].child[0],mx+1,rx,my+1,ry,max(x1,mx+1),x2,max(y1,my+1),y2);
    return ans;
}
map<int,int> mymap;
int main()
{
    int n,q,x;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        if(mymap[x]>0)
        {
            insert_point(0,0,n,0,n,mymap[x],i+1,1);
        }
        mymap[x]=i+1;
    }
    cin>>q;
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        cout<<(r-l+1-query(0,0,n,0,n,l,r,l,r))<<"\n";
    }
    return 0;
}
