#include <iostream>
#include <vector>
const int maxdist = 114514;
using namespace std;

/*n���ܵĽ����,
v�ǳ������,
dist�Ǿ���,
preǰһ�����,
d�ǽ����Ȩֵ*/
// Dijkstra(n, 0, dist, pre, d);
void Dijkstra(int n, int v, vector<int>& dist, vector<int>& pre, vector<vector<int>>& d) {
    vector<bool> s(n + 1);
    for (int i = 1; i <= n; i++) {
        dist[i] = d[v][i]; //��v��i�ڵ�ľ���浽dist[i]��
        // ����dist[1]�¾ʹ�Ŵ���ʼ�ڵ�v��1�ڵ�ľ���
        // ͬ��pre[1]�´��1�ڵ��ǰһ���ڵ㣬��ֻ�б�����С�˲Ż��
        if (dist[i] < maxdist)
            pre[i] = v;
        else
            pre[i] = 0;
    }
    // �Դ�����������������ʼ�ڵ�
    dist[v] = 0; // �Լ����Լ��ľ�������
    s[v] = true; // ���v��ʼ�ڵ��Ѿ��ҵ���С����
    for (int i = 2; i <= n; i++) {//�ܵ��������� ������ǰ�����Ĵ���ѭ��n - 1��
        int best = v; // ѭ����������ʼ�ڵ㣬 һ��ʼ��v�� ����ѭ�����лᷢ���仯
        int temp = maxdist; // 
        for (int j = 1; j <= n; j++) {//�ҵ���С�ľ���
            if (!s[j] && dist[j] < temp) { //��ǰ��ʼ�ڵ�û����С���������ڷ��ֻ��и���·��
                temp = dist[j]; // dist����������ʼ�ڵ㵽�����ڵ����С����
                best = j; // ��ʱѭ���������ᷢ���仯
            }
        }
        s[best] = true;
        for (int j = 1; j <= n; j++) {//����dist��pre
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
