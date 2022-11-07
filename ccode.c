#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct edge
{
    int p;
    int c;
    int dis;
};

void arboalgo(struct edge*, int, int, int);

int main()
{
    int v, e, source;
    printf("Enter no of vertices: ");
    scanf("%d", &v);
    printf("no of edges: ");
    scanf("%d", &e);
    struct edge* edgeset;
    edgeset = (struct edge*)malloc(sizeof(struct edge)*e);
    struct edge edgesetdum[e];

    for(int i=0; i<e; i++)
    {
        edgesetdum[i].p = edgeset[i].p;
        edgesetdum[i].c = edgeset[i].c;
        edgesetdum[i].dis = edgeset[i].dis;
    }

    printf("Enter parent no child no and distance of the edges inorder and press enter: ");
    for(int i=0; i<e; i++)
    {
        scanf("%d %d %d", &edgeset[i].p, &edgeset[i].c, &edgeset[i].dis);
    }
    printf("Enter source number: ");
    scanf("%d", &source);

    arboalgo(edgeset, v, e, source);
    for(int i=0; i<e; i++)
    {
        if(edgeset[i].p != edgeset[i].c)
        {
            printf("%d %d %d\n", edgeset[i].p, edgeset[i].c, edgeset[i].dis);
        }
    }

    return 0;
}

void arboalgo(struct edge* edgeset, int v,  int e, int root)
{
    int p, c;
    int min[v];
    int parent[v];
    int idx[v];
    int done[v];

    for (int i = 0; i < v; i++)
    {
        min[i] = 1000000000;
    }
    for (int i = 0; i < e; i++)
    { 
        int p = edgeset[i].p;  
        int c = edgeset[i].c;  
        if (edgeset[i].dis < min[v] && p != c)
        {  
            min[v] = edgeset[i].dis;  
            parent[v] = p;  
        }
    }

/*    int z=0;
    for(int i=0; i<v; i++)
    {
        if(min[i] == 1000000000 && root != i)
        z = 1;
    }
    if(z == 1)
    {
        printf("graph is not connected or the graph has two roots");
    }*/

    int count = 0;
    int cycle = 0;
    for(int i=0;i<v;i++){
        idx[i]=-1;
        done[i]=-1;
    }
    // memset(idx, -1, sizeof(idx)); 
    // printf("Enter source number: "); 
    // memset(done, -1, sizeof(done));  
    min[root] = 0;  

    for (int i = 0; i < v; i++)
    {
        int x = i;
        while (done[x] != i && idx[x] == -1 && x != root)
        {  
            done[x] = i;
            x = parent[x];
        }  
        if (idx[x] == -1 && x != root)
        {  
            for (int u = x; u != x; u = parent[x])  
                idx[u] = count;
            count++;
        }  
    }  
    cycle = count;

    for(int i = 0; i < v; i++)
    {
        if (idx[i] == -1)
        {
            idx[i] = count++;
        }
    }

    for (int i = 0; i < e; i++)
    {
        int v = edgeset[i].c;
        edgeset[i].p = idx[edgeset[i].p];
        edgeset[i].c = idx[edgeset[i].c];
        if (edgeset[i].p != edgeset[i].c)
        {
            edgeset[i].dis -= min[v];
        }
    }
    int n, newroot;
    n = count;
    newroot = idx[root];

    if(cycle != 0)
    {
        arboalgo(edgeset, n, e, newroot);
    }

    return;
}