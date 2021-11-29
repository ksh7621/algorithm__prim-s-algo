#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, m, q;
	cin >> n >> m >> q; //ver ed qu	
	vector<pair<int, int>> adjList[10001]; //인접 리스트 생성
	//unseen: 0 fringe: 1 tree: 2 상태 만들기
	//1. 모두 unseen 초기화
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
		//2. root 선택 status->root: 2로
		cin >> P >> S;
		visited.push_back(S);
		status[S] = 2;

		//3. 리스트 돌면서 (root)와 인접한 정점 status->fringe:1로 바꿔줌(초기)		
		for (int i = 0; i < adjList[S].size(); i++) {
			status[adjList[S][i].first] = 1;
			weight_set[adjList[S][i].first] = adjList[S][i].second;
		}		

		//반복해야함 다시 받아와서 다 tree 상태까지
		while (visited.size() != n) {
			min = 10001;
			idx = 0;
			//fringe 탐색 -> 최소로 미리 갱신 
			for (int i = 1; i <= n; i++){ // 정점기준
				if (status[i] == 1) { //fringe 이고
					if (weight_set[i] < min) { //최저일떄 갱신
						idx = i;
						min = weight_set[i];
					}else if (weight_set[i] == min) { //같을땐 빠른 index 선택->갱신하지 않음
						continue;
					}
				}
			}
			//3. 리스트 돌면서 인접한 정점 status->fringe:1로 바꿔줌, weight_set 추가				
			for (int j = 0; j < adjList[idx].size(); j++) {
				//unseen:0 -> fringe: 1
				if (status[adjList[idx][j].first] == 0) {
					status[adjList[idx][j].first] = 1;
					weight_set[adjList[idx][j].first] = adjList[idx][j].second;					
				}
				//fringe:1 -> weight 확인 값 갱신 여부 확인함 이전 weight가 더 작으면 그대로 아니면 바꿈				 
				else if (status[adjList[idx][j].first] == 1) {
					if (weight_set[adjList[idx][j].first] > adjList[idx][j].second) {
						weight_set[adjList[idx][j].first] = adjList[idx][j].second;
					}				
				}
				//seen:2 그냥 둠
				if (status[adjList[idx][j].first] == 2) {
					continue;
				}
			}
			//4. 정점 트리에 추가 status->tree:2로 바꿔줌 
			status[idx] = 2;			
			//visited vector에 추가 -> 순서 출력하기 위해
			visited.push_back(idx);				
		}

		//전체 cost 계산
		for (int i = 1; i <= n; i++) {
			mincost += weight_set[i];
		}

		//전체 출력
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
		//status-> unseen으로 초기화
		for (int i = 0; i <= n; i++) {
			status[i] = 0;
			weight_set[i] = 0;
		}
	}
	return 0;
}
