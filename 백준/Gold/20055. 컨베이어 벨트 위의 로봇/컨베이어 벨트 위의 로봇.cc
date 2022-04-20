#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
#define MAX 1000

int N, K;
int A[MAX] = {0, }; //밸트 내구도
int robot[MAX] = { 0, };	//로봇, 올라간 time으로 표시

void input()
{
	cin >> N >> K;
	for (int i = 0; i < 2*N; i++)
	{
		cin >> A[i];
	}
}

void move_belt()
{
	//벨트 한 칸 씩 이동(로봇이랑 같이)
	//내리는 위치 N-1 에 있는 로봇 내림

	//내구도(밸트) 한 칸 씩 이동
	for (int i = 2 * N; i > 0; i--)
	{
		A[i] = A[i - 1];
	}
	A[0] = A[2 * N];

	//로봇 한 칸 씩 이동
	for (int i = N; i > 0; i--)
	{
		robot[i] = robot[i - 1];
	}

	//내리는 위치 N-1에 있는 로봇 내림, 0이면 없는거
	robot[0] = 0;
	robot[N-1] = 0;
}



void move_robot()
{
	//로봇 이동
	//가장 먼저 올라간 로봇부터 하나씩 이동 O(2*N^2)
	//이동 불가능 -> 가만히
	//이동 조건 : 이동 할 칸에 로봇이 없고, 내구도가 1이상

	vector<pair<int, int> > temp;	//정렬을 위한 임시벡터
	
	for (int i = 0; i < N; i++)
	{
		if(robot[i]!=0) temp.push_back(make_pair(robot[i], i));	//임시 벡터에 로봇 들어온 순서와 인덱스 넣기
	}

	//오름차순 정렬
	sort(temp.begin(), temp.end());
	for (int i = 0; i < temp.size(); i++)
	{
		//정렬 된 순서대로 인덱스 탐색
		int	idx = temp[i].second;


		//N-1칸 전에 있고, 다음 칸에 로봇이 없고, 내구도 1이상이면 이동
		if (idx < N - 1 && robot[idx+1] == 0 && A[idx + 1] >= 1)
		{
			//한칸 이동
			robot[idx + 1] = robot[idx];
			robot[idx] = 0;
			//내구도 -1
			A[idx + 1] --;
		}
	}
	
	robot[N - 1] = 0; //내리는 위치 가면 무조건 내림
	
}

void put_on_belt(int time)
{
	//올리는 위치 idx : 0 에 로봇 올리기 & 내구도 -1
	//조건 : 내구도 1이상
	if (A[0] >= 1)
	{
		robot[0] = time;
		A[0] --;
	}
}

bool is_end()
{
	int cnt = 0;
	for (int i = 0; i < 2 * N; i++)
	{
		if (A[i] == 0) cnt++;
	}
	return cnt >= K ? true : false;
}

void print_state(string s)
{
	cout << s << "=====================\n";
	cout << "belt \n";
	for (int i = 0; i < N; i++)
	{
		cout << A[i] << ' ';
	}
	cout << " / ";
	for (int i = N; i < 2*N; i++)
	{
		cout << A[i] << ' ';
	}
	cout << "\n";

	cout << "robot \n";
	for (int i = 0; i < N; i++)
	{
		cout << robot[i] << ' ';
	}
	cout << " / ";
	for (int i = N; i < 2 * N; i++)
	{
		cout << robot[i] << ' ';
	}
	cout << "\n";
}

void solution()
{
	int time = 0;
	input();
	while(true)
	{
		time++; // 1~200000 까지, 로봇 올라간 순서
		//cout << time << "\n";
		//print_state("초기");
		move_belt();
		//print_state("밸트 이동 후");
		move_robot();
		//print_state("로봇 이동 후");
		put_on_belt(time);
		//print_state("로봇 놓은 후");
		if (is_end() == true) break;
	}
	cout << time;
}

int main()
{
	solution();
}