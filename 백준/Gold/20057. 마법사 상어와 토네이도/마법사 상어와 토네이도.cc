#include<iostream>

using namespace std;

#define MAX 499

int MAP[MAX][MAX];

int N;
int x, y; //현재 좌표
int dx[4] = {0,1,0,-1};
int dy[4] = { -1,0,1,0 };

//좌 하 우 상 

//좌 하 우 상 
int sand_percent_map[4][5][5] = { {{0, 0, 2, 0, 0 },
									{0, 10, 7, 1, 0},
									{5, 0, 0, 0, 0},
									{0, 10, 7, 1, 0},
									{0, 0, 2, 0, 0}},

								   {{0, 0, 0, 0, 0},
									{0, 1, 0, 1, 0},
									{2, 7, 0, 7, 2},
									{0, 10, 0, 10, 0},
									{0, 0, 5, 0, 0}},

									{{0, 0, 2, 0, 0 },
									{0, 1, 7, 10, 0},
									{0, 0, 0, 0, 5},
									{0, 1, 7, 10, 0},
									{0, 0, 2, 0, 0}},

								   {{0, 0, 5, 0, 0},
									{0, 10, 0, 10, 0},
									{2, 7, 0, 7, 2},
									{0, 1, 0, 1, 0},
									{0, 0, 0, 0, 0}} };
				


void input()
{
	cin >> N;
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
	x = N / 2;
	y = N / 2;
}

void print_map(int idx)
{
	cout << idx << "================================\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << MAP[i][j] << " ";
		}
		cout << "\n";
	}
}

void print_locate(int x, int y)
{
	cout << "================================\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == x && j == y) cout << 1 << " ";
			else cout << 0 << " ";
		}
		cout << "\n";
	}
}

int move_tonado(int d)
{
	//현재 좌표 이동
	x = x + dx[d] ;
	y = y + dy[d] ;
	int sand_origin = MAP[x][y];	//Y 에 남아있던 모래양
	int sand_alpha = 0;
	int sand_sum = 0;
	int sand_out = 0;

	MAP[x][y] = 0;	//Y칸 모든 모래 날아감
	//cout << x << "," << y <<"\n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int nx = x + i - 2;
			int ny = y + j - 2;

			if (nx < N && ny < N && nx >= 0 && ny >= 0)	//안나갔으면 좌표에 날린 모래 합치기
			{
				MAP[nx][ny] += sand_origin * sand_percent_map[d][i][j] / 100;
				sand_sum += sand_origin * sand_percent_map[d][i][j] / 100; //alpha칸 계산을 위함
			}
			else //나간 모래 계산
			{
				sand_out += sand_origin * sand_percent_map[d][i][j] / 100;
				sand_sum += sand_origin * sand_percent_map[d][i][j] / 100; //alpha칸 계산을 위함
			}
		}
	}
	sand_alpha = sand_origin - sand_sum;
	if (x + dx[d] < N && y + dy[d] < N && x + dx[d] >= 0 && y + dy[d] >= 0)
	{
		MAP[x + dx[d]][y + dy[d]] += sand_alpha;	//alpha칸 모래 합치기
	}
	else sand_out += sand_alpha;

	//cout << "sand_origin : " << sand_origin << ", sand_out : " << sand_out << "\n";
	return sand_out;
}


void solution()
{
	int sand_out = 0;
	input();
	init();
	for (int i = 0; i < N * 2 - 1; i ++)
	{
		int s = 0;		//이동할 거리
		if (i == N * 2 - 2) s = (i / 2);
		else s = (i / 2) + 1;
		int d = i % 4;	//이동할 방향
		for (int j = 0; j < s; j++)
		{
			sand_out += move_tonado(d);
			//cout << "sand_out sum : " << sand_out <<"\n";
			//print_map(i);
		}
	}
	cout << sand_out;
}

int main()
{
	solution();
	return 0;
}