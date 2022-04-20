#include<iostream>
#include<vector>
#include<utility>

using namespace std;

#define MAX 50

int MAP[MAX][MAX] = {0,};

int N, M;
int d[100] = { 0, }; //이동 방향
int s[100] = { 0, }; //이동 크기

int dx[9] = {0,  0, -1, -1, -1, 0, 1, 1,  1};
int dy[9] = {0, -1, -1,  0,  1, 1, 1, 0, -1};
//←, ↖, ↑, ↗, →, ↘, ↓, ↙

int dx_2[4] = {-1,-1,1,1};
int dy_2[4] = {-1,1,1,-1};
//↖, ↗, ↘, ↙

vector<pair<int, int> > c;

void input()
{
	cin >> N >>M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}
	for (int i = 0; i < M; i++)
	{
		cin >> d[i] >> s[i];
	}
}

void init()
{
	//초기 구름 생성 (N, 1), (N, 2), (N-1, 1), (N-1, 2)
	c.push_back(make_pair(N - 1, 0));
	c.push_back(make_pair(N - 1, 1));
	c.push_back(make_pair(N - 2, 0));
	c.push_back(make_pair(N - 2, 1));
}

void move_cloud(int idx)
{
	//구름이 d[idx] 방향으로, s[idx]칸 이동
	//N은 1과 붙어있음
	for (int i = 0; i < c.size(); i++)
	{
		//현재 구름 위치
		int x = c[i].first;
		int y = c[i].second;

		//d 방향으로 s칸 이동
		int nx = x + dx[d[idx]] * s[idx]; 
		int ny = y + dy[d[idx]] * s[idx];

		//N과 1이어 붙이기
		//이거때문에 1시간 추가 ㅎㅎ
		if (nx > N - 1) nx = nx%N;
		if (nx < 0) nx = nx%N == 0? 0:(nx % N) + N;
		if (ny > N - 1) ny = ny % N;
		if (ny < 0) ny = ny%N == 0? 0:(ny % N) + N;

		//구름 좌표 갱신
		c[i].first = nx;
		c[i].second = ny;
	}
}

void rain_shower()
{
	//구름의 위치에서 비가 내려 해당 칸 물의 양 1씩 증가
	for (int i = 0; i < c.size(); i++)
	{
		int x = c[i].first;
		int y = c[i].second;

		//cout << x << "," << y <<"\n";

		MAP[x][y] ++;
	}
}

void disapear_cloud()
{
	// 구름이 모두 사라진다
	c.clear();
}

void copy_water()
{
	// 물 복사 마법
	// 구름이 있던 칸에서 대각선 방향으로 물의 양이 1이상인 칸 만큼 해당 칸에 물 복사
	for (int i = 0; i < c.size(); i++)
	{
		
		int x = c[i].first;
		int y = c[i].second;

		//cout << "현재 좌표 : " << x << ',' << y << "\n";

		int cnt = 0;	//대각선 방향에 1이상인 칸 몇개인지

		for (int j = 0; j < 4; j++)
		{
			//대각선으로 한번씩 이동 해보기
			int nx = x + dx_2[j];
			int ny = y + dy_2[j];
			//cout << "대각선" << j << " : " << nx << ',' << ny << " : " << MAP[nx][ny] << "\n";
			if (nx<N && ny<N && nx>-1 && ny>-1) //밖으로 나간건 안됨
			{
				if (MAP[nx][ny] > 0)
				{
					cnt++;
				}
			}
		}
		MAP[x][y] += cnt; //cnt 만큼 물복사버그 시전
	}
}

void create_cloud()
{
	//바구니에 저장된 물의 양이 2이상인 모든 칸에 구름이 생기고
	//물의 양이 2줄어든다
	//이때 구름이 생기는 칸은 구름이 사라진(구름이 존재했던) 칸은 안됨
	

	//구름 맵 생성
	bool cloud_MAP[MAX][MAX] = { false, };
	for (int i = 0; i < c.size(); i++)
	{
		int x = c[i].first;
		int y = c[i].second;

		cloud_MAP[x][y] = true;
	}

	// 다쓴 구름 삭제
	c.clear(); 

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			//물의 양이 2이상이고, 구름이 없었으면 구름 생성
			//그리고 물의 양 2줄어든다
			if (MAP[i][j] >= 2 && cloud_MAP[i][j] == false)
			{
				c.push_back(make_pair(i, j));
				MAP[i][j] -= 2;
			}
		}
	}
}

int calculate_water()	
{
	//전체 맵의 물의 양 계산
	int sum = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			sum += MAP[i][j];
		}
	}
	return sum;
}
void print_cloud(string str)
{
	//구름 맵 생성
	bool cloud_MAP[MAX][MAX] = { false, };
	for (int i = 0; i < c.size(); i++)
	{
		int x = c[i].first;
		int y = c[i].second;

		cloud_MAP[x][y] = true;
	}

	cout << str << " cloud " << "\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (cloud_MAP[i][j] == true) cout << 1 << " ";
			else cout << 0 << " ";
		}
		cout << "\n";
	}
}

void print_map(string str)
{
	cout << str << "\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << MAP[i][j] << " ";
		}
		cout << "\n";
	}
	print_cloud(str);
}



void solution()
{
	input();
	init();
	
	for (int idx = 0; idx < M; idx++) // M번 반복(이동)
	{
		//cout << idx;
		//print_map("초기맵");
		move_cloud(idx);		//구름이동
		//cout << idx;
		//print_map("구름이동 후");
		rain_shower();		//비내림
		//cout << idx;
		//print_map("비내림 후");
		copy_water();		//물복사
		//cout << idx;
		///print_map("물복사 후");
		//disapear_cloud();	//구름 사라짐
		create_cloud();		//구름생성
		//cout << idx;
		//print_map("최종");
	}
	cout << calculate_water();		//물의 양 계산
}

int main()
{
	solution();
	return 0;
}