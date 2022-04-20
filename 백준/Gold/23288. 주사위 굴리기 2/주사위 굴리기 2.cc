#include<iostream>
#include<queue>

using namespace std;

#define MAX 20

struct pair_xy{
    int x;
    int y;
};

int map[MAX][MAX];

int N,M,K;
int r=0, c=0;

int dice[7] = {0,1,2,3,4,5,6};//주사위 바닥면 dice[6]
int dir = 0;    //주사위 방향, 초기값 동쪽

int dx[4] = {0,0,1,-1}; //동서남북
int dy[4] = {1,-1,0,0};

int point = 0;

void input()
{
    cin >> N >> M >> K;
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cin >> map[i][j];
        }
    }
}
void move_dice()//dice_num:바닥 숫자
{
    //주사위 이동, 막혀있으면 반대로
    
    //이동할 좌표
    int nx = r+dx[dir];
    int ny = c+dy[dir];
    if(nx >= N || ny >= M || nx < 0 || ny < 0)  //막혀있으면
    {
       switch(dir)  //방향 반대로 전환 동 <-> 서, 남 <-> 북
       {
            case 0:
                dir = 1;
                break;
            case 1:
                dir = 0;
                break; 
            case 2:
                dir = 3;
                break;
            case 3:
                dir = 2;
                break;
       }
        nx = r+dx[dir];
        ny = c+dy[dir];
    }

    int d1 = dice[1],d2 = dice[2],d3 = dice[3],d4 = dice[4],d5 = dice[5],d6 = dice[6];  //동서남북으로 움직였을때 주사위 위뒤오른왼앞밑 상태
    switch (dir)
    {
        case 0: //동
            dice[1] = d4, dice[2] = d2, dice[3] = d1, dice[4] = d6, dice[5] = d5, dice[6] = d3;
            break;
        case 1: //서
            dice[1] = d3, dice[2] = d2, dice[3] = d6, dice[4] = d1, dice[5] = d5, dice[6] = d4;
            break;
        case 2: //남
            dice[1] = d2, dice[2] = d6, dice[3] = d3, dice[4] = d4, dice[5] = d1, dice[6] = d5;
            break;
        case 3: //북
            dice[1] = d5, dice[2] = d1, dice[3] = d3, dice[4] = d4, dice[5] = d6, dice[6] = d2;
            break;            
    }
    
    //현재 주사위 좌표 갱신(이동 후)
    r=nx, c=ny;
}

//dfs 로 푸는법:dfs로 탐색하면서 같은숫자만 visit체크해주고 나중에 visit 개수 세기
//둘중에 아무거나 써도 상관없는데, 가중치 없는 최단경로 문제에서는 bfs밖에 못쓴다.
/*
int dfs(int x, int y, int d, int cnt)
{
    //이동할 좌표
    int nx = x + dx[d];
    int ny = y + dy[d];

    if(nx < N && ny < N && nx >= 0 && ny >=0)//칸 안벗어나면
    {
        if(map[x][y] == map[nx][ny])
        {
            dfs(nx,ny,(d+1)%4,cnt++);
        }
        else return cnt;
    }
}
*/

int bfs(int a, int b)   //bfs
{
    int cnt = 1;
    bool visit[MAX][MAX] = {false, };   //방문 체크용 맵

    queue<pair<int,int> > q;    //큐 선언

    q.push(make_pair(a,b));     //큐에 현재좌표 push. 큐에는 pair 써줘야됨
    visit[a][b] = true;

    while(!q.empty())       //큐가 빌때까지 반복
    {
        int x = q.front().first;    //현재 좌표 꺼내기
        int y = q.front().second;
        q.pop();     

        for(int i = 0; i<4; i++)    //현재좌표에서 갈 수 있는 방향 모두 탐색
        {
            int nx = x + dx[i];     //탐색할 좌표
            int ny = y + dy[i];

            if(nx < N && ny < M && nx >= 0 && ny >= 0 && visit[nx][ny] == false)//맵 안벗어나고, 방문 안했으면
            {
                if(map[x][y] == map[nx][ny]) //탐색했는데 숫자 같으면
                {
                    visit[nx][ny] = true;       //방문체크
                    cnt++;                      //개수세고
                    q.push(make_pair(nx,ny));   //현재 좌표 q에 넣기
                }
            }
        }
    }

    return cnt; //cnt가 0이면 1 아니면 cnt 반환
}

void get_point()
{
    //(현재칸에 있는 숫자로 동서남북 이어져있는 칸 X 현재 칸의 수 ) 만큼 점수 획득
    point += (map[r][c] * bfs(r,c));
    //cout << "point : " << point <<"\n";    
} 

void set_dir()
{
    //방향 설정
    // A > B인 경우 이동 방향을 90도 시계 방향으로 회전시킨다.
    // A < B인 경우 이동 방향을 90도 반시계 방향으로 회전시킨다.
    // A = B인 경우 이동 방향에 변화는 없다.
    int map_num = map[r][c];
    int dice_num = dice[6];

    if(dice_num > map_num) // 이동방향을 90도 시계방향으로 회전
    {
        switch(dir)
        {
            case 0: //동
                dir = 2; //남
                break;
            case 1: //서
                dir = 3; //북
                break;
            case 2: //남
                dir = 1; //서
                break;
            case 3: //북
                dir = 0; //동
                break;
        }
    }
    else if(dice_num < map_num) // 이동방향을 90도 반시계방향으로 회전
    {
        switch(dir)
        {
            case 0: //동
                dir = 3; //북
                break;
            case 1: //서
                dir = 2; //남
                break;
            case 2: //남
                dir = 0; //동
                break;
            case 3: //북
                dir = 1; //서
                break;
        }
    }
    else if(dice_num == map_num) // 변화 없음.
    {
        dir = dir;
    }

}

void solve()
{
    input();//입력
    for(int i = 0; i<K; i++)
    {
        //cout << i << " : ";
        //cout <<"("<< r <<"," << c<<")"<<" dir : "<<dir<<" dice : "<<dice[6]<<"\n";
        move_dice();//주사위 이동

        get_point();//점수 획득
        set_dir(); //주사위 방향 설정
    }
    cout << point;
}

int main()
{
    solve();
    return 0;
}