#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, m, q;
	cin >> n >> m >> q; //ver ed qu	
	vector<pair<int, int>> adjList[10001]; //���� ����Ʈ ����
	//unseen: 0 fringe: 1 tree: 2 ���� �����
	//1. ��� unseen �ʱ�ȭ
	int status[10001] = { 0, };	
	int weight_set[10001] = { 0, };
	vector<int> visited;
	char P;
	int S;
	int min = 10001;
	int idx = 0;
	int fromver, tover, weight;
	int mincost = 0; //total cost	
	

	while (m--) {
		cin >> fromver >> tover >> weight;
		//adjList
		adjList[fromver].push_back(make_pair(tover, weight));
		adjList[tover].push_back(make_pair(fromver, weight));
	}

	for (int qc = 0; qc < q; qc++) //query control
	{
		//2. root ���� status->root: 2��
		cin >> P >> S;
		visited.push_back(S);
		status[S] = 2;

		//3. ����Ʈ ���鼭 (root)�� ������ ���� status->fringe:1�� �ٲ���(�ʱ�)		
		for (int i = 0; i < adjList[S].size(); i++) {
			status[adjList[S][i].first] = 1;
			weight_set[adjList[S][i].first] = adjList[S][i].second;
		}		

		//�ݺ��ؾ��� �ٽ� �޾ƿͼ� �� tree ���±���
		while (visited.size() != n) {
			min = 10001;
			idx = 0;
			//fringe Ž�� -> �ּҷ� �̸� ���� 
			for (int i = 1; i <= n; i++){ // ��������
				if (status[i] == 1) { //fringe �̰�
					if (weight_set[i] < min) { //�����ϋ� ����
						idx = i;
						min = weight_set[i];
					}else if (weight_set[i] == min) { //������ ���� index ����->�������� ����
						continue;
					}
				}
			}
			//3. ����Ʈ ���鼭 ������ ���� status->fringe:1�� �ٲ���, weight_set �߰�				
			for (int j = 0; j < adjList[idx].size(); j++) {
				//unseen:0 -> fringe: 1
				if (status[adjList[idx][j].first] == 0) {
					status[adjList[idx][j].first] = 1;
					weight_set[adjList[idx][j].first] = adjList[idx][j].second;					
				}
				//fringe:1 -> weight Ȯ�� �� ���� ���� Ȯ���� ���� weight�� �� ������ �״�� �ƴϸ� �ٲ�				 
				else if (status[adjList[idx][j].first] == 1) {
					if (weight_set[adjList[idx][j].first] > adjList[idx][j].second) {
						weight_set[adjList[idx][j].first] = adjList[idx][j].second;
					}				
				}
				//seen:2 �׳� ��
				if (status[adjList[idx][j].first] == 2) {
					continue;
				}
			}
			//4. ���� Ʈ���� �߰� status->tree:2�� �ٲ��� 
			status[idx] = 2;			
			//visited vector�� �߰� -> ���� ����ϱ� ����
			visited.push_back(idx);				
		}

		//��ü cost ���
		for (int i = 1; i <= n; i++) {
			mincost += weight_set[i];
		}

		//��ü ���
		if (visited.size() == n)
		{
			cout << mincost << " ";
			for (int b = 0; b < visited.size(); b++)
			{
				cout << visited[b] << " ";
			}
			cout << endl;
		}
		//init
		mincost = 0;
		visited.clear();		
		//status-> unseen���� �ʱ�ȭ
		for (int i = 0; i <= n; i++) {
			status[i] = 0;
			weight_set[i] = 0;
		}
	}
	return 0;
}
