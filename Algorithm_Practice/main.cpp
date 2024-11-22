//#include "Dijkstra.hpp"
#include "Reference_test1.hpp"

int main() {
    int n, l;
    cout << "请输入结点数和线数：";
    cin >> n >> l;
    vector<vector<int>> d(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            d[i][j] = maxdist; //二维数组下全部填最大
    }

    // 利用二维数组的方式表示图，可能有很多无效结点
    int p, q, len;
    for (int i = 1; i <= l; ++i) {
        cin >> p >> q >> len; //节点p到节点q的长度是len
        if (len < d[p][q]) {       // 有重边
            d[p][q] = len;      // p指向q
            d[q][p] = len;      // q指向p，这样表示无向图
        }
    }
    vector<int> dist(n + 1), pre(n + 1);
    for (int i = 1; i <= n; ++i)
        dist[i] = maxdist;


    Dijkstra(n, 0, dist, pre, d);
    cout << "点0到点n的最短路径长度: " << dist[n] << endl;
    cout << "点0到点n的路径为: ";
    printpath(pre, 0, n);

    return 0;
}
