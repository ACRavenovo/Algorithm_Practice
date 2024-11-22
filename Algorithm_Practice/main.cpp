//#include "Dijkstra.hpp"
#include "Reference_test1.hpp"

int main() {
    int n, l;
    cout << "������������������";
    cin >> n >> l;
    vector<vector<int>> d(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            d[i][j] = maxdist; //��ά������ȫ�������
    }

    // ���ö�ά����ķ�ʽ��ʾͼ�������кܶ���Ч���
    int p, q, len;
    for (int i = 1; i <= l; ++i) {
        cin >> p >> q >> len; //�ڵ�p���ڵ�q�ĳ�����len
        if (len < d[p][q]) {       // ���ر�
            d[p][q] = len;      // pָ��q
            d[q][p] = len;      // qָ��p��������ʾ����ͼ
        }
    }
    vector<int> dist(n + 1), pre(n + 1);
    for (int i = 1; i <= n; ++i)
        dist[i] = maxdist;


    Dijkstra(n, 0, dist, pre, d);
    cout << "��0����n�����·������: " << dist[n] << endl;
    cout << "��0����n��·��Ϊ: ";
    printpath(pre, 0, n);

    return 0;
}
