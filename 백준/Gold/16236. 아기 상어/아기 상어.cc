#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX 20

int N, M;
int MAP[MAX][MAX];

int dx[4] = {-1,1,0,0};
int dy[4] = { 0,0,1,-1 };

int eat_time = 0;
int total_time = 0;
bool is_need_a_help = false;
int eat_cnt = 0;

struct SHARK
{
	int x, y;
	int size;
};

SHARK shark;

void input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
			if (MAP[i][j] == 9)
			{
				shark.x = i;
				shark.y = j;
				shark.size = 2;
			}
		}
	}
}

void grow_up_shark()
{
	//자신의 크기만큼 먹으면  +1 하고 카운트 초기화
	if (eat_cnt == shark.size)
	{
		shark.size++;
		eat_cnt = 0;
	}
}

int find_route()
{
	//처음 상어의 크기는 2
	//한칸 이동할때 마다 시간 t +1;
	//자신의 크기와 작거나 같은 물고기 칸만 지나갈 수 있음
	//자신의 크기보다 작으면 먹을 수 있음
	//먹을 수 있는 물고기가 많으면 가장 가까운 물고기, 위칸, 왼쪽칸 물고기 순으로 먹음
	// -> 같은 t중에서 sort 정렬 해서 뽑으면 됨

	//처음상어 크기 2, 좌표
	int x = shark.x;
	int y = shark.y;
	int size = shark.size;

	//탐색할 후보 넣을 큐 - 좌표랑 이동하는 데 걸리는 시간 t 들어감
	struct LOCATE
	{
		int x, y;
		int t;
	};

	LOCATE loc;

	queue<LOCATE> Q;
	queue<LOCATE> Q_candi;

	//탐색표시
	bool visit[MAX][MAX] = {false,};

	//현재좌표, 시간 넣기
	loc.x = x, loc.y = y, loc.t = 0;
	Q.push(loc);
	visit[loc.x][loc.y] = true;

	eat_time = 0;

	bool flag = false;
	//BFS
	while (!Q.empty())
	{
		//탐색 목록 중 하나 꺼내기
		loc = Q.front();
		int x = loc.x;
		int y = loc.y;
		int pre_t = loc.t;
		//cout << loc.x << "," << loc.y << "," << loc.t<<"\n";
		try		
		{
			Q.pop();
		}
		catch (int exception)
		{
			continue;
		}
		
		//탐색 목록 중 하나 꺼냈는데 flag 랑 같으면 종료. - 해당 시간과 같은 좌표는 탐색 끝났다는것.
		if (loc.t == eat_time && flag == true) break;
		
		for (int i = 0; i < 4; i++)
		{
			//인접한 좌표 탐색
			int nx = x + dx[i];
			int ny = y + dy[i];
			//cout << nx <<"," << ny<<"\n";
			//탐색할 수 있는 조건 만족하면 탐색
			//조건 : 탐색안한곳, 범위안에 드는곳, 자신보다작거나 같은 물고기
			if (visit[nx][ny] == false && (nx >= 0 && ny >= 0 && nx < N && ny < N) && (MAP[nx][ny] <= shark.size))
			{
				//방문 표시
				visit[nx][ny] = true;

				//탐색목록 큐에 삽입
				loc.x = nx, loc.y = ny, loc.t = pre_t+1;
				Q.push(loc);

				//먹을 수 잇는 물고기(상어크기보다 작은 물고기)가 있으면, flag 세우고 큐에 저장
				if (shark.size > MAP[nx][ny]&& MAP[nx][ny]!=0)
				{	
					//cout << "real candi : " << nx << "," << ny << '\n';
					flag = true;
					eat_time = loc.t;
					Q_candi.push(loc);
				}
			}
		}
	}
	//먹을 수 있는 후보가 없으면 엄마 도움 필요 - 종료
	if (Q_candi.size() == 0)
	{
		is_need_a_help = true;
		return 0;
	}
	//진짜 먹으러 갈 물고기 찾기
	vector<pair<int,int> > v;
	//cout << "Q_cnadi size : " << Q_candi.size() << '\n';
	while (!Q_candi.empty())
	{
		loc = Q_candi.front();					
		//cout << "candi : " << loc.x << "," << loc.y << '\n';
		try {
			Q_candi.pop();
		}
		catch (exception)
		{
			continue;
		}
		v.push_back(make_pair(loc.x,loc.y));
	}
	std::sort(v.begin(), v.end());

	//먹으러 갈 좌표
	int fish_x = v.front().first;
	int fish_y = v.front().second;
	//cout << "pick : " << fish_x << "," << fish_y << '\n';

	//물고기 먹음
	MAP[fish_x][fish_y] = 9;
	MAP[shark.x][shark.y] = 0;
	//cout << "fish_loc" << fish_x << "," << fish_y<<"\n";
	shark.x = fish_x;
	shark.y = fish_y;
	eat_cnt++;

	//total_time 갱신
	total_time += (eat_time);
	
	//상어 자라기
	grow_up_shark();
	return 0;
}
void print_map()
{
	cout << "=======================\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << MAP[i][j] << " ";
		}
		cout << "\n";
	}
	
}


void solution()
{
	input();
	while (true)
	{
		find_route();
		grow_up_shark();
		//print_map();
		if (is_need_a_help == true) break;

	}
	cout << total_time;
}



int main()
{
	solution();

	return 0;
}