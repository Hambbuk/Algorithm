#include<iostream>
#include<vector>
#include<cmath>
#include<queue>

#define MAX 25
using namespace std;

int N = 0;
struct student
{
	int s;
	int like[4];
};
struct candidate
{
	queue<int> cnt_like;
	queue<int> cnt_empty;
	queue<int> x;
	queue<int> y;
};
int map[MAX][MAX] = { 0, };
student sdt[1000];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };


void input()
{
	cin >> N;
	int N_2 = pow(N, 2);

	for (int i = 0; i < N_2; i++)
	{
		cin >> sdt[i].s;
		for (int k = 0; k < 4; k++)
		{
			cin >> sdt[i].like[k];
		}
	}
}

void init()
{
	map[1][1] = sdt[0].s;
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
}

void put_student(int sdt_idx)
{
	int N_2 = N * N;
	int cnt_like = 0;
	int cnt_empty = 0;
	int temp[MAX][MAX] = { 0, };
	candidate candi;
	int max = 0;
	int max_like = 0;
	int max_empty = 0;
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N;y++)
		{
			for (int i = 0; i < 4; i++)
			{
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx < N && nx >= 0 && ny < N && ny >= 0)
				{
					for (int j = 0; j < 4; j++)
					{
						if (sdt[sdt_idx].like[j] == map[nx][ny])
						{
							cnt_like++;
						}
					}
					if (map[nx][ny] == 0) cnt_empty++;
				}
			}
			
			candi.cnt_like.push(cnt_like);
			candi.cnt_empty.push(cnt_empty);
			candi.x.push(x);
			candi.y.push(y);
			cnt_like = 0;
			cnt_empty = 0;
		}
	}
	max = 0;
	int x=0, y=0;


	int start = 0;
	while (!candi.cnt_like.empty())
	{
		if (start == 0 && map[candi.x.front()][candi.y.front()] == 0)
		{
			max_like = candi.cnt_like.front();
			max_empty = candi.cnt_empty.front();
			x = candi.x.front();
			y = candi.y.front();

			start = 1;
		}
		if (candi.cnt_like.front() > max_like && map[candi.x.front()][candi.y.front()] ==0)
		{
			max_like = candi.cnt_like.front();
			max_empty = candi.cnt_empty.front();
			x = candi.x.front();
			y = candi.y.front();
		}
		if (candi.cnt_like.front() == max_like && candi.cnt_empty.front()>max_empty && map[candi.x.front()][candi.y.front()] == 0)
		{
			max_like = candi.cnt_like.front();
			max_empty = candi.cnt_empty.front();
			x = candi.x.front();
			y = candi.y.front();
		}
		//cout << sdt[sdt_idx].s << " : " << max_like << " " << max_empty << " " << x << " " << y << "\n";


		candi.cnt_like.pop();
		candi.cnt_empty.pop();
		candi.x.pop();
		candi.y.pop();
	}
	map[x][y] = sdt[sdt_idx].s;
}

int get_answer()
{
	int N_2 = pow(N, 2);
	int cnt_like = 0;
	int answer = 0;
	for (int sdt_idx = 0; sdt_idx < N_2; sdt_idx++)
	{
		for (int x = 0; x < N; x++)
		{
			for (int y = 0; y < N; y++)
			{
				if (map[x][y] == sdt[sdt_idx].s)
				{
					for (int i = 0; i < 4; i++)
					{
						int nx = x + dx[i];
						int ny = y + dy[i];
						if (nx < N && nx >= 0 && ny < N && ny >= 0)
						{
							for (int j = 0; j < 4; j++)
							{
								if (sdt[sdt_idx].like[j] == map[nx][ny])
								{
									cnt_like++;
								}
							}
						}
					}
				}
			}
		}
		if (cnt_like == 0) answer += 0;
		else if (cnt_like == 1) answer += 1;
		else if (cnt_like == 2) answer += 10;
		else if (cnt_like == 3) answer += 100;
		else if (cnt_like == 4) answer += 1000;
		cnt_like = 0;
	}
	return answer;
}

void solve()
{
	input();
	init();
	int N_2 = pow(N, 2);
	for (int i = 1; i < N_2; i++)
	{
		put_student(i);
	}
	cout << get_answer();
}


int main(int argc, char** argv)
{

	solve();

	return 0;
}