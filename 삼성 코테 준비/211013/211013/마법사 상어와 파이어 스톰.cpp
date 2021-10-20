#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
using namespace std;
#define MAX 128

int map[MAX][MAX] = {0, };
int N, Q;
vector<int> L;
bool visit[MAX][MAX] = {false, };

int dy[4] = { 0,-1,0,1 };
int dx[4] = { -1,0,1,0 };

void input()
{
	cin >> N >> Q;
	N = (1 << N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < Q; i++)
	{
		int L_input;
		cin >> L_input;
		L.push_back(L_input);
	}
}

void print_map()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int BFS(int a, int b)
{
	queue<pair<int, int>> Q;
	Q.push(make_pair(a, b));
	visit[a][b] = true;
	int cnt = 1;

	while (!Q.empty())
	{
		int x = Q.front().first;
		int y = Q.front().second;
		Q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx < N && nx >= 0 && ny < N && ny >= 0)
			{
				if (visit[nx][ny] == false && map[nx][ny] != 0)
				{
					visit[nx][ny] = true; 
					Q.push(make_pair(nx, ny));
					cnt++;
				}
			}
		}
	}
	return cnt;
}

int get_mass()
{
	int result = 0;
	int max = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (visit[i][j] == false && map[i][j] != 0)
			{
				result = BFS(i,j);
				max = max > result ? max : result;
			}
		}
	}
	return max;
}


void melt()
{
	int ny, nx;
	int cnt = 0;
	int temp[MAX][MAX] = {0, };
	queue<pair<int, int>> Q;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (map[r][c] == 0) continue;
			for (int i = 0; i < 4; i++)
			{
				ny = r + dy[i];
				nx = c + dx[i];
				if (ny < N && ny>-1 && nx < N && nx>-1)
				{
					if (map[ny][nx] != 0) cnt++;
				}
			}
			if (cnt < 3)
			{
				temp[r][c] = map[r][c] - 1;
				Q.push(make_pair(r,c));
			}
			cnt = 0;
		}
	}
	while (!Q.empty())
	{
		int r = Q.front().first;
		int c = Q.front().second;
		map[r][c] = temp[r][c];
		Q.pop();
	}

}

void rotate(int cnt)
{
	int temp[MAX][MAX] = { 0, };
	int rotated_temp[MAX][MAX] = { 0, };
	int L_size = 1 << L[cnt];
	int x=0, y = 0;

	while (1)
	{
		for (int i = 0; i < L_size; i++)
		{
			for (int j = 0; j < L_size; j++)
			{
				temp[i][j] = map[i+x][j+y];
			}
		}

		for (int i = 0; i < L_size; i++)
		{
			for (int j = 0; j < L_size; j++)
			{
				rotated_temp[j][L_size-1-i] = temp[i][j];
			}
		}

		for (int i = 0; i < L_size; i++)
		{
			for (int j = 0; j < L_size; j++)
			{
				map[i + x][j + y] = rotated_temp[i][j];
			}
		}

		if ((x == N - L_size) && (y == N - L_size))
		{
			break;
		}

		if (y == N - L_size)
		{
			x += L_size;
			y = 0;
		}
		else y += L_size;
	}

}

int sum_ice()
{
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			sum += map[i][j];
		}
	}
	return sum;
}

void solve()
{
	for (int i = 0; i < Q; i++)
	{
		rotate(i);
		melt();
	}
	cout << sum_ice() <<"\n";
	cout << get_mass();
}

int main(int argc, char** argv)
{
	input();
	solve();
	return 0;
}