#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//structure to store edge
struct edge
{
    int p;//from vertex or parent
    int c;//to vertex or child
    int dis;//weight of edge
};

void arboalgo(struct edge*, int, int, int);
void elimination(struct edge*, int*, int, int);

int main()
{
    //G=(V,E,W)
    int v, e, source;//No. of Vertices,Edges;Source Vertex
    printf("Enter no of vertices: ");
    scanf("%d", &v);//V={0,1,2,3,4....v-1}
    printf("no of edges: ");
    scanf("%d", &e);
    struct edge* edgeset;//Set of edges that undergoes modification
    edgeset = (struct edge*)malloc(sizeof(struct edge)*e);
    struct edge edgesetdum[e];//Array of Structures that represent edge original version
    //E={edgesetdum[i].p,edgesetdum[i].c|0<=i<e}
    //W={edgesetdum[i].dis|0<=i<e}
    printf("Enter parent no., child no. and distance of the edges inorder and press enter: ");
    for(int i=0; i<e; i++)
    {
        scanf("%d %d %d", &edgeset[i].p, &edgeset[i].c, &edgeset[i].dis);
        getchar();
    }
    for(int i=0; i<e; i++)
    {
        edgesetdum[i].p = edgeset[i].p;
        edgesetdum[i].c = edgeset[i].c;
        edgesetdum[i].dis = edgeset[i].dis;
    }

    printf("Enter source number: ");
    scanf("%d", &source);

    arboalgo(edgeset, v, e, source);

    int* enco;
    enco = (int*)malloc(sizeof(int)*e);

    elimination(edgeset, enco, source, e);

    int parent[v], prevdis[v];
    int mincost = 0;
    for(int i=0; i<e; i++)
    {
        if(edgeset[i].dis == 0)
        {
            parent[edgeset[i].c] = edgeset[i].p;
            prevdis[edgeset[i].c] = edgesetdum[i].dis;
            mincost += edgesetdum[i].dis;
        }
    }
    printf("The minimum cost is %d\n",mincost);
    parent[source] = -1;

    int mindist[v];
    for(int i=0; i<v; i++)
    {
        int loc = i;
        while(loc != source)
        {
            mindist[i] += prevdis[loc];
            loc = parent[loc];
        }
    }
    mindist[source] = 0;

    printf("edges in the minimum cost spanning tree of the given graph are:\n");
    for(int i=0; i<e; i++)
    {
        if(edgeset[i].dis == 0)
        {
            printf("%d %d %d\n", edgeset[i].p, edgeset[i].c, edgesetdum[i].dis);
        }
    }

    return 0;
}

void arboalgo(struct edge* edgeset, int v,  int e, int root)
{
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
        if (edgeset[i].dis < min[c] && p != c)
        {  
            min[c] = edgeset[i].dis;
            parent[c] = p;
        }
    }
    parent[root] = -1;

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
    for(int i=0; i<v; i++)
    {
        idx[i] = -1;
        done[i] = -1;
    }
    min[root] = 0;

    for (int i = 0; i < v; i++)///////////
    {
        int x = i;
        while (done[x] != i && idx[x] == -1 && x != root)
        {  
            done[x] = i;
            x = parent[x];
        }
        if (idx[x] == -1 && x != root)
        {
            for (int j = parent[x]; j != x; j = parent[j])
            {
                idx[j] = count;
            }
            idx[x] = count++;
        }
    }  
    cycle = count;////////////

    for(int i = 0; i < v; i++)
    {
        if (idx[i] == -1)
        {
            idx[i] = count++;
        }
    }
    struct edge* nedgeset;
    nedgeset = (struct edge*)malloc(sizeof(struct edge)*e);

    for (int i = 0; i < e; i++)
    {
        nedgeset[i].p = idx[edgeset[i].p];
        nedgeset[i].c = idx[edgeset[i].c];
        if (edgeset[i].p != edgeset[i].c)
        {
            edgeset[i].dis -= min[edgeset[i].c];
            nedgeset[i].dis = edgeset[i].dis;
        }
    }
    int newroot;
    newroot = idx[root];

/*    for(int i=0; i<e; i++)
    {
        if(edgeset[i].p != edgeset[i].c)
        {
            printf("%d %d %d\n", edgeset[i].p, edgeset[i].c, edgeset[i].dis);
        }
    }*/


    if(cycle != 0)
    {
        arboalgo(nedgeset, count, e, newroot);
    }
    for(int i=0; i<e; i++)
    {
        if(nedgeset[i].dis == 0)
        {
            edgeset[i].dis = 0;
        }
    }

    return;
}

void elimination(struct edge* edgeset, int* enco, int parnt, int e)
{
    enco[parnt] = 1;

    for(int i=0; i<e; i++)
    {
        if(edgeset[i].p == parnt && edgeset[i].c != parnt && edgeset[i].dis == 0)
        {
            if(enco[edgeset[i].c] == 1)
            {
                edgeset[i].dis = 1;
            }
            else
            {
                elimination(edgeset, enco, edgeset[i].c, e);
            }
        }
    }
}
