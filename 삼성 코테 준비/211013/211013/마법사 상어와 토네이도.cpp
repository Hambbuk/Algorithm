#include<iostream>
#include<vector>


using namespace std;

int N;
int r, c;
int MAP[500][500];

vector<pair<int, int>> dir = { {0,-1}, {1,0}, {0,1}, {-1,0} };

int sand_percent_map[4][5][5] = { { {0,0,2,0,0},
								{0,10,7,1,0},
								{5,0,0,0,0},
								{0,10,7,1,0},
								{0,0,2,0,0} },
	                          { {0,0,0,0,0},
								{0,1,0,1,0},
								{2,7,0,7,2},
								{0,10,0,10,0},
								{0,0,5,0,0} },
							  { {0,0,2,0,0},
								{0,1,7,10,0},
								{0,0,0,0,5},
								{0,1,7,10,0},
								{0,0,2,0,0} },
							  { {0,0,5,0,0},
								{0,10,0,10,0},
								{2,7,0,7,2},
								{0,1,0,1,0},
								{0,0,0,0,0} }};

void Input()
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

void Init()
{
	r = N / 2 ;
	c = N / 2 ;
}

int changeDir(int idx)
{
	if (idx == 3) return 0;
	else return idx+1;
}

void printMap()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << MAP[i][j]<<" ";
		}
		cout << "\n";
	}
}

void print_rc(int r, int c)
{
	cout << r << "," << c <<"\n";
}

int moveSand(int dir_idx)
{
	int origin_sand = MAP[r][c];
	//cout << "origin_sand : " << origin_sand<<"\n";
	int moved_sand = 0;
	int out_sand = 0;
	int sum_sand = 0;
	int a = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (sand_percent_map[dir_idx][i][j] == 0) continue;
			moved_sand = (sand_percent_map[dir_idx][i][j] * origin_sand) / 100;
			//cout << "sand_percent : " << sand_percent_map[dir_idx][i][j] << "\n" ;
			//cout << "sand_amount : " << (sand_percent_map[dir_idx][i][j] * origin_sand) / 100 << "\n";

			if (r - 2+i < 0 || r - 2+i > N - 1 || c - 2+j < 0 || c - 2+j > N - 1)
			{
				out_sand += moved_sand;
				//cout << "out_sand : " << r - 2 + i << "," << c - 2 + j << ":" << out_sand << "\n";
			}
			else
			{
				MAP[r - 2 + i][c - 2 + j] += moved_sand;
				//cout << "moved_sand : " << r - 2 + i << "," << c - 2 + j << ":" << moved_sand << "\n";
			}
			//printMap();
			sum_sand += moved_sand;
		}
	}
	if (r + dir[dir_idx].first < 0 || r + dir[dir_idx].first > N - 1 || c + dir[dir_idx].second < 0 || c + dir[dir_idx].second > N - 1)
	{
		out_sand += origin_sand - sum_sand;
	}
	else
	{
		MAP[r + dir[dir_idx].first][c + dir[dir_idx].second] += (origin_sand - sum_sand);
	}
	MAP[r][c] = 0;
	//printMap();
	return out_sand;
}

int Solution()
{
	int dir_idx = 0;
	int cnt = 0;
	int move_cnt = 1;
	int answer = 0;
	while(1)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < move_cnt; j++)
			{
				r += dir[dir_idx].first;
				c += dir[dir_idx].second;

				//cout << r << "," << c << ":" << MAP[r][c]<<"\n";
				answer += moveSand(dir_idx);
				
				//printMap();
			}
			dir_idx = changeDir(dir_idx);
		}
		move_cnt++;
		if (move_cnt == N)
		{
			for (int i = 0; i < move_cnt-1; i++)
			{
				r += dir[dir_idx].first;
				c += dir[dir_idx].second;

				//cout << r << "," << c << ":" << MAP[r][c]<<"\n";
				answer += moveSand(dir_idx);
				//printMap();
			}
			break;
		}
	}
	return answer;
}

void Solve()
{
	Input();
	Init();
	cout << Solution() << "\n";
}
int main(int argc, char** argv)
{

	Solve();

	return 0;
}