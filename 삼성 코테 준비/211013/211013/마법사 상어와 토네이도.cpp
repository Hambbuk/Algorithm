#include<iostream>
#include<vector>

using namespace std;

int N;
int r, c;
int MAP[500][500];

vector<pair<int, int>> dir = { {0,-1}, {1,0}, {0,1}, {-1,0} };

void Input()
{
	cin >> N;
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

void moveSand()
{

}

void Solution()
{
	int dir_idx = 0;
	int cnt = 0;
	int move_cnt = 1;
	while(1)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < move_cnt; j++)
			{
				r += dir[dir_idx].first;
				c += dir[dir_idx].second;

				cnt++;
				MAP[r][c] = cnt;
			}
			dir_idx = changeDir(dir_idx);
		}
		move_cnt++;
		if (move_cnt == N)
		{
			for (int i = 0; i < move_cnt; i++)
			{
				r += dir[dir_idx].first;
				c += dir[dir_idx].second;

				cnt++;
				MAP[r][c] = cnt;
				

			}
			break;
		}
	}
}

void Solve()
{
	Input();
	Init();
	Solution();
	printMap();
}
int main(int argc, char** argv)
{
	Solve();
	return 0;
}