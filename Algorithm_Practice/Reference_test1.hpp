#include <iostream>
#include <vector>
const int maxdist = 114514;
using namespace std;

/*n是总的结点数,
v是出发结点,
dist是距离,
pre前一个结点,
d是结点间的权值*/
// Dijkstra(n, 0, dist, pre, d);
void Dijkstra(int n, int v, vector<int>& dist, vector<int>& pre, vector<vector<int>>& d) {
    vector<bool> s(n + 1);
    for (int i = 1; i <= n; i++) {
        dist[i] = d[v][i]; //从v到i节点的距离存到dist[i]里
        // 比如dist[1]下就存放从起始节点v到1节点的距离
        // 同理，pre[1]下存放1节点的前一个节点，且只有比无穷小了才会存
        if (dist[i] < maxdist)
            pre[i] = v;
        else
            pre[i] = 0;
    }
    // 以此类推做完推演完起始节点
    dist[v] = 0; // 自己到自己的距离是零
    s[v] = true; // 标记v起始节点已经找到最小距离
    for (int i = 2; i <= n; i++) {//总迭代次数， 这里就是把下面的代码循环n - 1次
        int best = v; // 循环的最优起始节点， 一开始是v， 随着循环进行会发生变化
        int temp = maxdist; // 
        for (int j = 1; j <= n; j++) {//找到最小的距离
            if (!s[j] && dist[j] < temp) { //当前起始节点没有最小距离且现在发现还有更优路径
                temp = dist[j]; // dist里面存的是起始节点到各个节点的最小距离
                best = j; // 这时循环最优起点会发生变化
            }
        }
        s[best] = true;
        for (int j = 1; j <= n; j++) {//更新dist和pre
            if (!s[j] && d[best][j] != maxdist) {
                int newdist = dist[best] + d[best][j];
                if (newdist < dist[j]) {
                    dist[j] = newdist;
                    pre[j] = best;
                }
            }
        }
    }
}

void printpath(vector<int> pre, int init, int fina) {
    int temp = fina;
    vector<int> t;
    while (temp != init) {
        t.push_back(temp);
        temp = pre[fina];
        fina = temp;
    }
    cout << init << "->";
    for (int i = t.size(); i > 1; i--)cout << t[i - 1] << "->";
    cout << t[0];
    t.clear();
}
