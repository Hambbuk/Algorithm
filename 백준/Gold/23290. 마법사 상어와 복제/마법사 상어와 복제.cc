#include<iostream>
#include<vector>
#include<fstream>
#include <stdio.h>

#define MAX 1000000

using namespace std;

int M; //물고기 수
int S; //마법 연습 횟수

struct fish {
	int x;
	int y;
	int d;
};

struct fish_list {
	int i;
	int j;
	int k;
};

struct shark {
	int x;
	int y;
};


struct direct {
	int dx;
	int dy;
};

vector<fish> temp;
//←, ↖, ↑, ↗, →, ↘, ↓, ↙
direct dir[8] = { {0,-1},{-1,-1},{-1,0}, {-1,1},{0,1},{1,1},{1,0},{1,-1} };
//↑, ←, ↓, →
direct dir_shrk[4] = { {-1,0} ,{0,-1},{1,0} ,{0,1} };
shark shrk;

vector<fish> fish_map[4][4];
vector<fish> copy_map[4][4];
vector<fish_list> can_move_list;

int smell_map[4][4] = { 0, };

int route[3], temp_route[3];
int eat_max = 0;

bool route_flag = true;


void input()
{
	int x = 0, y = 0, d = 0;
	cin >> M >> S;

	for (int i = 0; i < M; i++)
	{
		cin >> x >> y >> d;
		x--, y--, d--;
		fish f = { x,y,d };
		fish_map[x][y].push_back(f);
	}

	cin >> shrk.x >> shrk.y;
	shrk.x--;
	shrk.y--;
}

void init()
{
	eat_max = 0;
	route_flag = true;
}

void print_map(string s)
{
	cout << "=====================================\n";
	cout << s <<"\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == shrk.x && j == shrk.y) cout << "S ";
			else cout << fish_map[i][j].size() << " ";
		}
		cout << "\n";
	}
	/*
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << fish_map[i][j].size();
			if (fish_map[i][j].size() > 0)
			{
				for(int cnt = 0 ; cnt<fish_map[i][j].size(); cnt++)	cout << "/" << fish_map[i][j][cnt].d ;
			}
			cout << " ";
		}
		cout << "\n";
	}
	cout << "상어위치 : " << shrk.x <<"," << shrk.y << "\n";
	cout << "\n냄새 칸\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << smell_map[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	*/
	cout << "=====================================\n";

}

void magic_cpy()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//vector 복사
			copy_map[i][j] = fish_map[i][j];
		}
	}
}

bool can_move(int x, int y, int k)
{
	//이동하고자 하는 칸의 좌표 : 현재칸 + 방향
	int nx = x + dir[fish_map[x][y][k].d].dx;
	int ny = y + dir[fish_map[x][y][k].d].dy;
	//상어가 있는 칸, 물고기의 냄새가 있는 칸, 격자의 범위를 벗어나는 칸으로는 이동 불가

	//상어 있는 칸
	if (nx == shrk.x && ny == shrk.y) return false;

	//물고기 냄새 칸
	else if (smell_map[nx][ny] != 0) return false;

	//격자 범위 벗어나는 칸
	else if (nx >= 4 || ny >= 4 || nx < 0 || ny < 0) return false;

	//다 통과 하면 움직일 수 있는것으로 판단
	else return true;
}

int turn_fish(int i, int j, int k)
{
	//움직일 수 있는 애들 list저장
	if (can_move(i, j, k) == true)
	{
		can_move_list.push_back({ i,j,k });
		return true;
	}
	//못움직이면 움직일 수 있을 때까지 45도 턴
	else
	{
		for (int cnt = 0; cnt < 8; cnt++)
		{
			fish_map[i][j][k].d = fish_map[i][j][k].d > 0 ? ((fish_map[i][j][k].d - 1)) : fish_map[i][j][k].d + 7;
			//cout << "\n" << i << " " << j << " : " << fish_map[i][j][k].d << "\n";
			if (can_move(i, j, k) == true)
			{
				return true;
			}
		}
	}
	return false; //8번 돌았는데도 못움직이는 물고기
}

void move_fish()
{
	//temp_map 생성
	vector<fish> temp_map[4][4];

	//방향설정and 이동
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (fish_map[i][j].size() != 0)
			{
				for (int k = 0; k < fish_map[i][j].size(); k++)
				{
					bool flag = turn_fish(i, j, k);

					if (flag == true) // 움직일 수 있는 친구 : 이동
					{
						int nx = i + dir[fish_map[i][j][k].d].dx;
						int ny = j + dir[fish_map[i][j][k].d].dy;
						temp_map[nx][ny].push_back(fish_map[i][j][k]);
					}
					else if (flag == false) // 못움직이는 친구 :그대로
					{
						temp_map[i][j].push_back(fish_map[i][j][k]);
					}
				}
			}
		}
	}
	//temp 맵에 넣어놨던거 다시 fish 맵으로 복사 
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//vector 복사
			fish_map[i][j] = temp_map[i][j];
		}
	}
}


int route_simulation()
{
	bool visit[4][4] = { false, };
	int eat = 0;
	int x = shrk.x;
	int y = shrk.y;

	for (int i = 0; i < 3; i++)
	{
		// nx, ny : 이동할 좌표, x, y : 현재 좌표
		int nx = x + dir_shrk[temp_route[i]].dx;
		int ny = y + dir_shrk[temp_route[i]].dy;
		// 맵 벗어나면 -1 반환하고 종료
		if (nx > 3 || ny > 3 || nx<0 || ny < 0) return -1;
		// 방문 안한 곳만 물고기 먹음(이미 먹은거 중복 방지)
		if (visit[nx][ny] == false)
		{
			eat += fish_map[nx][ny].size();
			visit[nx][ny] = true;
		}
		//이동할 좌표로 현재 좌표 이동(방문한 곳도 갈 수 있음)
		x = nx;
		y = ny;
	}
	//cout << "eat : " << eat << "{" << temp_route[0]<< temp_route[1]<<temp_route[2] << "}" << "\n";
	//루트 다 돌아보고 먹은 물고기 반환
	return eat;
}

// 중복 순열 돌리면서 모든 경우의 수 루트 생성하는 함수
int find_route(int cnt)
{
	// 루트 완성했으면 루트대로 한번 가보기(루트 길이 3)
	if (cnt == 3)
	{
		//cout << "생성된 루트 :";
		//cout << temp_route[0] << temp_route[1] << temp_route[2]<<"\n";
		int eat_num = route_simulation();
		//돌아봤는데 최대 크기면 저장 or 처음으로 max값이면
		if ((eat_num != -1 && route_flag == true) || eat_max < eat_num)
		{
			route_flag = false;
			eat_max = eat_num;
			for (int i = 0; i < 3; i++)
			{
				route[i] = temp_route[i];
			}
		}
		//생성한 루트 돌아봤으면 다음 루트 생성
		return 0;
	}
	//루트 생성, 맨 뒷자리 부터 하나씩 바꿈(중복순열)
	for (int i = 0; i < 4; i++)
	{
		// 상은 1, 좌는 2, 하는 3, 우는 4
		temp_route[cnt] = i;
		find_route(cnt + 1);
	}
	return 0;
}

void move_shark(int time)
{
	//상어 연속 3칸 이동
	// 상은 1, 좌는 2, 하는 3, 우는 4
	//최대값 루트로 이동

	//현재 상어 좌표
	int x = shrk.x;
	int y = shrk.y;

	int nx, ny;
	//cout <<"\n" << route[0] << route[1] << route[2] << "\n";
	//3칸 이동했을 때 좌표 계산
	for (int i = 0; i < 3; i++)
	{
		nx = x + dir_shrk[route[i]].dx;
		ny = y + dir_shrk[route[i]].dy;
		//먹은 물고기 냄새 남기기, 최신 냄새가 몇번째인지만 남기면 됨
		if (fish_map[nx][ny].size() > 0)
		{
			//상어가 지나간 칸의 모든 물고기 삭제, 냄새 남기기
			smell_map[nx][ny] = time;
			fish_map[nx][ny].clear();
		}
		x = nx;
		y = ny;
	}

	//3칸 실제 이동
	shrk.x = nx;
	shrk.y = ny;
}

void remove_smell(int time)
{
	//2턴 지난 냄새 제거
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (time - smell_map[i][j] >= 2) smell_map[i][j] = 0;
		}
	}
}

void update_magic()
{
	//복제된 물고기 생성
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < copy_map[i][j].size(); k++)
			{
				fish_map[i][j].push_back(copy_map[i][j][k]);
			}
			copy_map[i][j].clear();
		}
	}
}

int fish_num()
{
	int sum = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sum += fish_map[i][j].size();
		}
	}
	return sum;
}

void solve()
{
	input();
	for (int time = 1; time <= S; time++)
	{
		init();
		//cout << "TIME : " << time << "\n";
		//print_map("초기출력"); // 디버깅용

		magic_cpy();

		move_fish(); //물고기 한칸 이동

		//print_map("물고기 이동 후"); // 디버깅용
		
		find_route(0);
		move_shark(time); //상어 3칸 이동

		//print_map("상어 이동 후"); // 디버깅용
		
		remove_smell(time); //2턴 지난 냄새 제거
		update_magic(); //복제된 물고기 생성

		//print_map("물고기 복제 마법 시전 후"); // 디버깅용
	}
	cout << fish_num(); //남은 물고기 수 출력
}

int main()
{
	solve();
	return 0;
}