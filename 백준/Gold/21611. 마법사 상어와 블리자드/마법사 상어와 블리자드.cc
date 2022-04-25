#include<iostream>
#include<vector>

using namespace std;
#define MAX 49

int N, M;
int MAP[MAX][MAX] = {-1, };
int d[100], s[100];
vector<int> vec_MAP;
vector<pair<int, int>> dir = { {0,0}, {-1,0}, {1,0}, {0,-1}, {0,1} };
vector<pair<int, int>> grp;
int p[3] = { 0, };

void Input()
{
	cin >> N >> M;
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
	cout << "\n";
}

void printVec()
{
	for (int i = 0; i < vec_MAP.size(); i++)
	{
		cout << vec_MAP[i] << " ";
	}
	cout << "\n";
}

void map_to_vec()
{
	int flag = 1;
	int r=0, c=0;
	r = ((N + 1) / 2)-1;
	c = ((N + 1) / 2)-1;

	vec_MAP.clear();	
	//빙글 도는 순서대로 vec_MAP에 넣기

	for (int i = 0; i <= N; i++)
	{
		if (i == 0) vec_MAP.push_back(-2); //-2는 상어
		else
		{
			flag *= -1;
			for (int j = 1; j <= i; j++)
			{
				c += flag;
				vec_MAP.push_back(MAP[r][c]);
				if (r==0 && c==0) break;
			}
			if (r == 0 && c == 0) break;
			flag *= -1;
			for (int j = 1; j <= i; j++)
			{
				r += flag;
				vec_MAP.push_back(MAP[r][c]);
				
			}
			flag *= -1;
		}

	}
}

void vec_to_map()
{
	int flag = 1;
	int r = 0, c = 0;
	int cnt = 1;
	r = ((N + 1) / 2) - 1;
	c = ((N + 1) / 2) - 1;

	for (int i = 0; i <= N; i++)
	{
		if (i == 0) MAP[r][c] = -2; //-2는 상어
		else
		{
			flag *= -1;
			for (int j = 1; j <= i; j++)
			{
				c += flag;
				MAP[r][c] = vec_MAP[cnt];
				cnt++;
				if (r == 0 && c == 0) break;
			}
			if (r == 0 && c == 0) break;
			flag *= -1;
			for (int j = 1; j <= i; j++)
			{
				r += flag;
				MAP[r][c] = vec_MAP[cnt];
				cnt++;

			}
			flag *= -1;
		}

	}
}

void throwIce(int idx)
{
	int row = dir[d[idx]].first;
	int col = dir[d[idx]].second;
	for (int i = 1; i <= s[idx] ; i++)
	{
		MAP[((N + 1) / 2) + row * i-1][((N + 1) / 2) + col * i-1] = 0;
	}
}

void moveMarble()
{
	int size = vec_MAP.size();
	int idx = 0;
	for (int i = 0; i < size; i++)
	{
		if (vec_MAP[idx] == 0)
		{
			vec_MAP.push_back(0);
			vec_MAP.erase(vec_MAP.begin() + idx);
			idx--;
		}
		idx++;
	}
}

void popMarble()
{
	int cnt = 0;
	for (int i = 1; i < vec_MAP.size(); i++)
	{
		if (vec_MAP[i] == vec_MAP[i - 1]) cnt++;
		else
		{
			if (cnt > 2)
			{
				p[vec_MAP[i - 1] - 1] += cnt+1;
				for (int j = 0; j < cnt+1; j++)
				{
					vec_MAP[i-j-1] = 0;
				}
			}
			cnt = 0;
		}
	}
}

bool isStable()
{
	int cnt = 0;
	for (int i = 1; i <= vec_MAP.size(); i++)
	{
		if (vec_MAP[i] == vec_MAP[i - 1])
		{
			cnt++;
			if (vec_MAP[i] == 0) return true;
		}
		else cnt = 0;
		if (cnt > 2) return false;
	}
	return true;   
}

void groupMarble()
{
	int cnt = 1;
	grp.clear();
	for (int i = 1; i < vec_MAP.size(); i++)
	{
		if (vec_MAP[i] == vec_MAP[i - 1]) cnt++;
		else
		{
			grp.push_back(make_pair(cnt, vec_MAP[i - 1]));
			cnt = 1;
		}
	}
	vec_MAP.clear();
	vec_MAP.push_back(-2); // 상어
	for (int i = 1; i < grp.size(); i ++)
	{
		vec_MAP.push_back(grp[i].first);
		vec_MAP.push_back(grp[i].second);
	}
	for (int i = grp.size(); i < N*N; i++)
	{
		vec_MAP.push_back(0);
	}
}
int getAnswer()
{
	int answer = 0;
	answer = p[0] + p[1] * 2 + p[2] * 3;
	return answer;
}

int Solution()
{
	Input();

	map_to_vec();
	for (int i = 0; i < M; i++)
	{
		throwIce(i);
		map_to_vec();
		moveMarble();
		vec_to_map();
		while (!isStable())
		{
			popMarble();
			moveMarble();
			vec_to_map();
		}
		groupMarble();
		vec_to_map();
	}
	return getAnswer();
}

int main(int argc, char** argv)
{
	cout << Solution();

	return 0;
}