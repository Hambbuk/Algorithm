#include<iostream>

using namespace std;

#define MAX 50

int N, M;
int r, c, d;

int clean_cnt = 0;

int map[MAX][MAX];

int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

struct ROBOT
{
	int x, y;
	int d;
};

ROBOT robot;

void input()
{
	cin >> N >> M;
	cin >> robot. x >> robot.y >> robot.d;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
		}
	}
}

void clean()
{
	//현재 위치 청소
	int x = robot.x;
	int y = robot.y;

	if (map[x][y] == 0)
	{
		//청소한 곳은 -1 표시
		map[x][y] = 2;

		//청소한 칸 개수
		clean_cnt++;
	}
}

bool search_a()
{
	for (int cnt = 0; cnt < 4; cnt++)
	{
		//현재 로봇상태
		int x = robot.x;
		int y = robot.y;
		int d = robot.d;
		//왼쪽
		int left = (d + 3) % 4;

		//왼쪽으로 회전,이동했을때 좌표
		int nx = x + dx[left];
		int ny = y + dy[left];

		//a.왼쪽에 청소안한 공간 존재
		if (map[nx][ny] == 0 && nx<N && ny<M && nx>=0&& ny>=0)
		{
			//왼쪽으로 회전, 이동
			robot.x = nx;
			robot.y = ny;
			robot.d = left;
			//cout << "true\n";
			return true;
		}
		//왼쪽에 청소 안한 칸 없으면 just 회전
		else
		{
			robot.d = left;
		}
	}
	//cout << "false\n";
	return false;
}

bool search_b()
{
	//b.a단계가 4번 연속 실행 됐을때 실행
	//바로 뒤 좌표
	int back = (robot.d + 2) % 4;
	int nx = robot.x + dx[back];
	int ny = robot.y + dy[back];

	//바로 뒤가 벽이면 멈춤
	if (map[nx][ny] == 1) return true;
	//아니면 후진 1칸
	else if(nx < N && ny < M && nx >= 0 && ny >= 0)
	{
		robot.x = nx;
		robot.y = ny;
		//robot.d = back;
		return false;
	}
}

void print_map()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "==================\n";
}

void solution()
{
	input();

	//바로 뒤가 벽일때까지 반복
	while (true)
	{
		//현재 위치 청소
		clean();

		//탐색 - search_a가 참이면 clean(), 거짓이면 search_b()호출
		if (search_a()) ;
		else
		{
			if (search_b()) break;
		}
		//print_map();
	}
	cout << clean_cnt;
}

int main()
{
	solution();

	return 0;
}