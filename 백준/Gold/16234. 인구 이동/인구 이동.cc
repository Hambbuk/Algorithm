#include<iostream>
#include<vector>
#include<cmath>
#include<queue>

using namespace std;

#define MAX 100

int MAP[MAX][MAX];
pair<int, int> open_list[MAX][MAX][4];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int N, L, R;

bool is_end = false;

void input()
{
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}
}

void init()
{
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			for (int i = 0; i < 4; i++)
			{
				open_list[x][y][i].first = -1;
				open_list[x][y][i].second = -1;
			}
		}
	}
}
void open_door()
{
	//인접한 나라 중 현재 나라와 인구 수 차이가 L이상 R이하면 국경 개방
	//현재 나라와 국경개방하면 open_list에 추가
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			for (int i = 0; i < 4; i++)
			{
				//탐색할 좌표
				int nx = x + dx[i];
				int ny = y + dy[i];

				//범위 안에 들면 탐색
				if (nx >= 0 && ny >= 0 && nx < N && ny < N)
				{
					//조건 만족하면 개방 리스트에 추가
					//조건 : 인구 수 차이가 L이상 R이하면 국경 개방
					if (L <= (abs(MAP[x][y] - MAP[nx][ny])) && (abs(MAP[x][y] - MAP[nx][ny]) <= R))
					{
						//cout << x<< "," << y <<" " << MAP[x][y] << "->" << nx << "," << ny<<" " << MAP[nx][ny] << "here!\n";
						//x,y 좌표의 i 방향으로 가면 개방국 존재
						open_list[x][y][i].first = nx;
						open_list[x][y][i].second = ny;
					}
				}
			}
		}
	}

}


void move_people()
{
	//bfs 로 개방국 탐색하면서 vector에 넣고 인구 이동
	//visit 체크해야됨

	int visit[MAX][MAX] = {false, };
	vector<pair<int, int> > alli_list;

	//종료 flag 세워놓고 하나라도 이동하면 다시 false
	is_end = true;

	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			//현재 좌표에서 상하좌우로 이동하면서 현재 좌표와 이어진 국가 표시
			queue<pair<int, int> > Q;

			Q.push(make_pair(x, y));
			visit[x][y] = true;

			while (!Q.empty())
			{
				
				int cx = Q.front().first;
				int cy = Q.front().second;
				Q.pop();
				//cout << "현재 탐색좌표 : ";
				//cout << cx << "," << cy << "\n";

				alli_list.push_back(make_pair(cx, cy));
				for (int i = 0; i < 4; i++)
				{
					//탐색할 좌표
					int nx = cx + dx[i];
					int ny = cy + dy[i];

					//탐색가능하면 - 범위내, 방문안한곳
					if ((nx < N && ny < N && nx >= 0 && ny >= 0) && visit[nx][ny] == false)
					{
						//cout << nx << "," << ny << "\n";

						
						//현재좌표를 연합국 리스트에 추가

						//연합국이 하나라도 있으면 탐색 목록에 추가
						for (int j = 0; j < 4; j++)
						{
							//현재좌표랑 다음좌표랑 연합국이면 다음 좌표를 탐색 목룍에 추가 
							if ((open_list[cx][cy][j].first == nx) && (open_list[cx][cy][j].second == ny))
							{
								//방문 표시
								visit[nx][ny] = true;
								//cout << cx << "," << cy << " -> " << nx << "," << ny<<"\n";
								//vector에 집어넣고, Q-탐색목록에 집어넣음
								Q.push(make_pair(nx, ny));
							}
						}
					}
				}
			}
			//현재좌표에서 갈 수 있는 동맹국 인구이동
			//연합국 인구수/연합을 이루고 있는 칸의 개수
			int sum_people = 0;
			int sum_alli = alli_list.size();
			for (int i = 0; i < sum_alli; i++)
			{
				int x = alli_list[i].first;
				int y = alli_list[i].second;
				sum_people += MAP[x][y];
			}

			for (int i = 0; i < sum_alli; i++)
			{
				int x = alli_list[i].first;
				int y = alli_list[i].second;
				MAP[x][y] = sum_people / sum_alli;
				//cout << x<<"," << y<<" : "<< sum_people/sum_alli << "\n";
			}
			if (alli_list.size() > 1) is_end = false;
			alli_list.clear();
			//cout << sum_alli << "\n";
		}
	}

}


void close_door()
{
	//연합을 해체하고, 모든 국경선을 닫는다.
	init();
}

void print_map()
{
	cout << "==============================\n";
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			cout << MAP[x][y] << " ";
		}
		cout << "\n";
	}
}

void solution()
{
	input();
	init();
	int day = 0;
	while (!is_end)
	{
		//cout << "wow\n";
		open_door();
		move_people();
		//print_map();
		close_door();
		if(!is_end) day++;
	}
	cout << day;
}


int main()
{

	solution();

	return 0;
}