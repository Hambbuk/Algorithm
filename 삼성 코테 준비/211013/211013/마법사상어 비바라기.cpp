/////////////////////////////////////////////////////////////////////////////////////////////
// �⺻ �����ڵ�� ���� �����ص� ���� �����ϴ�. ��, ����� ���� ����
// �Ʒ� ǥ�� ����� ���� �ʿ�� �����ϼ���.
// ǥ�� �Է� ����
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int ���� 1�� �Է¹޴� ����
// cin >> b >> c;                       // float ���� 2�� �Է¹޴� ���� 
// cin >> d >> e >> f;                  // double ���� 3�� �Է¹޴� ����
// cin >> g;                            // char ���� 1�� �Է¹޴� ����
// cin >> var;                          // ���ڿ� 1�� �Է¹޴� ����
// cin >> AB;                           // long long ���� 1�� �Է¹޴� ����
/////////////////////////////////////////////////////////////////////////////////////////////
// ǥ�� ��� ����
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int ���� 1�� ����ϴ� ����
// cout << b << " " << c;               // float ���� 2�� ����ϴ� ����
// cout << d << " " << e << " " << f;   // double ���� 3�� ����ϴ� ����
// cout << g;                           // char ���� 1�� ����ϴ� ����
// cout << var;                         // ���ڿ� 1�� ����ϴ� ����
// cout << AB;                          // long long ���� 1�� ����ϴ� ����
/////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<vector>

using namespace std;

int N, M;
int MAP[55][55] = { 0, };
int d[100], s[100];
bool Cloud_MAP[55][55];

vector<pair<int, int>> Cloud;
vector<pair<int, int>> dir = { {0,0},{0,-1}, {-1,-1}, {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1} };


void Print_MAP()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << MAP[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void Print_Cloud()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << (Cloud_MAP[i][j] == true) ? 1 : 0;
			cout << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void Input()
{
	cin >> N >> M;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			cin >> MAP[r][c];
		}
	}
	for (int i = 0; i < M; i++)
	{
		cin >> d[i] >> s[i];
	}
}

void Init_Cloud()
{
	Cloud.push_back(make_pair(N - 2, 0));
	Cloud.push_back(make_pair(N - 2, 1));
	Cloud.push_back(make_pair(N - 1, 0));
	Cloud.push_back(make_pair(N - 1, 1));

	Cloud_MAP[N - 2][0] = true;
	Cloud_MAP[N - 2][1] = true;
	Cloud_MAP[N - 1][0] = true;
	Cloud_MAP[N - 1][1] = true;
}

int Make_Range(int a)
{
	if (a % N == 0) return 0;
	else if (a < 0) return (N + (a % N));
	else if (a > (N - 1)) return (a % (N));
	else return a;
}

void Move_Cloud(int idx)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Cloud_MAP[i][j] = false;
		}
	}
	for (int i = 0; i < Cloud.size(); i++)
	{
		Cloud[i].first = Cloud[i].first + dir[d[idx]].first * s[idx];
		Cloud[i].second = Cloud[i].second + dir[d[idx]].second * s[idx];

		Cloud[i].first = Make_Range(Cloud[i].first);
		Cloud[i].second = Make_Range(Cloud[i].second);
		Cloud_MAP[Cloud[i].first][Cloud[i].second] = true;
	}

}

void Make_Rain()
{
	for (int i = 0; i < Cloud.size(); i++)
	{
		MAP[Cloud[i].first][Cloud[i].second]++;
	}

}

void Delete_Cloud()
{
	Cloud.clear();
}

void Water_Bug()
{
	for (int i = 0; i < Cloud.size(); i++)
	{
		int cnt = 0;
		if (Cloud[i].first > 0)
		{
			if (MAP[Cloud[i].first - 1][Cloud[i].second + 1] > 0) cnt++;
		}
		if (Cloud[i].second > 0)
		{
			if (MAP[Cloud[i].first + 1][Cloud[i].second - 1] > 0) cnt++;
		}
		if (Cloud[i].first > 0 && Cloud[i].second > 0)
		{
			if (MAP[Cloud[i].first - 1][Cloud[i].second - 1] > 0) cnt++;
		}
		if (MAP[Cloud[i].first + 1][Cloud[i].second + 1] > 0) cnt++;

		MAP[Cloud[i].first][Cloud[i].second] = MAP[Cloud[i].first][Cloud[i].second] + cnt;
	}

}

void Make_Cloud()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (MAP[i][j] < 2 || Cloud_MAP[i][j] == true) continue;
			MAP[i][j] -= 2;
			Cloud.push_back(make_pair(i, j));
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Cloud_MAP[i][j] = false;
		}
	}

	for (int i = 0; i < Cloud.size(); i++)
	{
		Cloud_MAP[Cloud[i].first][Cloud[i].second] = true;
	}
}

int Find_Answer()
{
	int answer = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			answer += MAP[i][j];
		}
	}
	return answer;
}


int Solution()
{
	Input();
	Init_Cloud();

	for (int i = 0; i < M; i++)
	{
		Move_Cloud(i);

		Make_Rain();

		Water_Bug();

		Delete_Cloud();

		Make_Cloud();

	}

	return Find_Answer();

}

int main(int argc, char** argv)
{

	cout << Solution();

	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}