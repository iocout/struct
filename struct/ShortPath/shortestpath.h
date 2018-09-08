/**
* @projectName   ShortPath
* @brief         寻找图的最短路径，即Dijkstra算法（缔结拉特算法）
*                这里的图必须是带权图，而且权必须大于0
* @author        HF
* @date          2018-09-08
*/

#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "myExceptions.h"
#include "chain.h"
#include "graphChain.h"

const int noEdge=65535;//整型最大值，用来表示两条不相邻边的权值

template<class T>
void shortestPaths(int sourceVertex, T* distanceFromSource,int * predecesor)
{//寻找从原点sourceVertex开始的最短路径
    //数组predecesor表示每个点的前驱
    if(sourceVertex <1 || sourceVertex>n)
       throw illegalParameterValue("Invaild source vertex");
    //缺少确认*this是加权图的代码

    //记录到达的路径，可以用一个小根堆来表示，每次从其中取出权值最小的，
    //表示到达的下一个节点
    graphChain<int> newReachableVertices;

    //初始化,此时所有不邻接与初始顶点的点的前驱为-1
    for(int i=1;i<=n;i++)
    {
        //a是一个图的邻接矩阵，a[b][c]表示从点b到点c的距离
        //注意的是这儿未邻接b的点的距离都为
        distanceFromSource[i]=a[sourceVertex][i];
        if(distanceFromSource[i]==noEdge)
            predecesor[i]=-1;
        else
        {
            //邻接于起始点的前驱为起始点
            predecesor[i] = sourceVertex;
            //将邻接点放入小根堆
            newReachableVertices.insert(0,i);
        }
    }
    distanceFromSource[sourceVertex]=0;//起始点的权值为0
    predecesor[sourceVertex]=0;//源顶点前驱为0。

    //不断更新distanceFromSource和predecesor
    while(!newReachableVertices.empty())//小根堆中有值
    {
        //存在更多的路径
        //从小根堆中取出根节点，其权值最小，表示到达的路径最短
        chain<int>::iterator iNewReachableVertices=newReachableVertices.begin();
        chain<int>::iterator theEnd=newReachableVertices.end();

        int v=*iNewReachableVertices; //取出点的当前值
        iNewReachableVertices++;//于取出点相邻的边
        while(iNewReachableVertices!=theEnd)
            int w=*iNewReachableVertices;//邻接于取出点的点
            iNewReachableVertices++;
            //取出其中的最小值
            if(distanceFromSource[w]<distanceFromSource[v])
                v=w;
    }
    //下一条最短路径是到达顶点v
    //从newReachableVertices中删除顶点v,然后更新distanceFromSource
    newReachableVertices.eraseElement(v);
    for(int j=1;j<=n;j++)
    {
        if(a[v][j]!=noEdge&&(predecesor[j]==-1 ||
          distanceFromSource[j]>distanceFromSource[v]+a[v][j]))
        {
            //distanceFromSource[j]减少
            distanceFromSource[j]=distanceFromSource[v]+a[v][j];
            //把顶点j加到newreachablevetices
            if(predecesor==-1)
                //新加进来的点必须是从未到达的
                //如果已经到达过，表示此时求得路径不是最小路径
                newReachableVertices.insert(0,j);
            predecesor[j]=v;
        }
    }
}

#endif // SHORTESTPATH_H
