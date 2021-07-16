#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>


#define MAXR		99
#define MAXC		26

int table[99][26];
int g_C, g_R;
int cnt=0;

void init(int C, int R) {
	g_C = C;
	g_R = R;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			table[i][j] = 1000000001;
			if(table[i][j] == 1000000001) printf("¤±");
		    else printf("%d", table[i][j]);
		}
		printf("\n");
	}
}

void set(int col, int row, char input[]) {
	row--;
	col--;

	int pre_col, pre_row, post_col, post_row;
	int idx = 4;
	pre_col = input[idx] - 65;
	if (input[idx + 2] != 44)
	{
		pre_row = (input[idx + 1] - 48) * 10 + (input[idx + 2] - 49);
		idx += 1;
	}
	else pre_row = input[idx + 1] - 49;

	post_col = input[idx + 3] - 65;
	if (input[idx + 5] != 41) post_row = (input[idx + 4] - 48) * 10 + (input[idx + 5] - 49);
	else post_row = input[idx + 4] - 49;

	//printf("\npre_col :%d pre_row : %d \n", pre_col, pre_row);
	//printf("\npost_col :%d post_row : %d \n", post_col, post_row);
	if (input[0] == 'A' && input[1] == 'D' && input[2] == 'D')
	{
		printf("ADD!\n");
		table[row][col] = 1000000000 + 1*100000000 + pre_col * 1000000 + pre_row * 10000 + post_col * 100 + post_row;
		//table[row][col] = table[pre_row][pre_col]+ table[pre_row][pre_col];
	}
	else if (input[0] == 'S' && input[1] == 'U' && input[2] == 'B')
	{
		printf("SUB!\n");
		table[row][col] = 1000000000 + 2 * 100000000 + pre_col * 1000000 + pre_row * 10000 + post_col * 100 + post_row;
		//table[row][col] = table[pre_row][pre_col] - table[pre_row][pre_col];
	}
	else if (input[0] == 'M' && input[1] == 'U' && input[2] == 'L')
	{
		printf("MUL!\n");
		table[row][col] = 1000000000 + 3 * 100000000 + pre_col * 1000000 + pre_row * 10000 + post_col * 100 + post_row;
		//table[row][col] = table[pre_row][pre_col] * table[pre_row][pre_col];
	}
	else if (input[0] == 'D' && input[1] == 'I' && input[2] == 'V')
	{
		printf("DIV!\n");
		table[row][col] = 1000000000 + 4 * 100000000 + pre_col * 1000000 + pre_row * 10000 + post_col * 100 + post_row;
		//table[row][col] = table[pre_row][pre_col] / table[pre_row][pre_col];
	}
	else if (input[0] == 'M' && input[1] == 'A' && input[2] == 'X')
	{
		printf("MAX!\n");
		table[row][col] = 1000000000 + 5 * 100000000 + pre_col * 1000000 + pre_row * 10000 + post_col * 100 + post_row;
		//int max = table[pre_row][pre_col];
		//if (pre_row == post_row)
		//{
		//	for (int i = pre_col; i <= post_col; i++)
		//	{
		//		if(table[pre_row][i]>max) max = table[pre_row][i];
		//	}
		//}
		//else
		//{
		//	for (int i = pre_row; i <= post_row; i++)
		//	{
		//		if (table[i][pre_col] > max) max = table[i][pre_col];
		//	}
		//}
		//table[row][col] = max;
	}
	else if (input[0] == 'M' && input[1] == 'I' && input[2] == 'N')
	{
		printf("MIN!\n");
		table[row][col] = 1000000000 + 6 * 100000000 + pre_col * 1000000 + pre_row * 10000 + post_col * 100 + post_row;
		//int min = table[pre_row][pre_col];
		//if (pre_row == post_row)
		//{
		//	for (int i = pre_col; i <= post_col; i++)
		//	{
		//		if (table[pre_row][i] < min) min = table[pre_row][i];
		//	}
		//}
		//else
		//{
		//	for (int i = pre_row; i <= post_row; i++)
		//	{
		//		if (table[i][pre_col] < min) min = table[i][pre_col];
		//	}
		//}
		//table[row][col] = min;
	}
	else if (input[0] == 'S' && input[1] == 'U' && input[2] == 'M')
	{
		printf("SUM!\n");
		table[row][col] = 1000000000 + 7 * 100000000 + pre_col * 1000000 + pre_row * 10000 + post_col * 100 + post_row;
		//int sum = 0;
		//if (pre_row == post_row)
		//{
		//	for (int i = pre_col; i <= post_col; i++)
		//	{
		//		printf("(%d,%d) %d\n", i, pre_row, table[pre_row][i]);
		//		sum = sum + table[pre_row][i];
		//	}
		//}
		//else
		//{
		//	for (int i = pre_row; i <= post_row; i++)
		//	{
		//		printf("(%d,%d) %d\n", i, pre_row, table[pre_row][i]);
		//		sum = sum + table[i][pre_col];
		//	}
		//}
		//table[row][col] = sum;
	}
	else
	{
		int num = 0;
		if (input[0] == 45)
		{
			for (int i = 1; i < 12; i++)
			{
				if (input[i] == '\0') break;
				num = num * 10 + (input[i] - 48);
			}
			num = num * -1;
		}
		else
		{
			for (int i = 0; i < 11; i++)
			{
				if (input[i] == '\0') break;
				num = num * 10 + (input[i] - 48);
			}
		}
		table[row][col] = num;
	}
}


int spot_update(int table[MAXR][MAXC], int spot_row, int spot_col) {
	//printf("\n=================================================\n");
	//for (int i = 0; i < 5; i++)
	//{
	//	for (int j = 0; j < 5; j++)
	//	{
	//		if (table[i][j] == 1000000001)
	//		{
	//			table[i][j] = 0;
	//			printf(" ¤± ");
	//		}
	//		else if (table[i][j] > 1000000001)
	//		{
	//			table[i][j] = spot_update(table, i, j);
	//			printf(" %d ", table[i][j]);
	//		}
	//		else
	//		{
	//			printf(" %d ", table[i][j]);
	//		}
	//	}
	//	printf("\n");
	//}
	//printf("\n=================================================\n");

	cnt++;

	if (table[spot_row][spot_col] < 1000000001) return table[spot_row][spot_col];

	int cmd = (table[spot_row][spot_col] % 1000000000) / 100000000;
	int pre_col = table[spot_row][spot_col] % 100000000 / 1000000;
	int	pre_row = table[spot_row][spot_col] % 1000000 / 10000;
	int	post_col = table[spot_row][spot_col] % 10000 / 100;
	int	post_row = table[spot_row][spot_col] % 100;
	int max, min, sum = 0;

	switch (cmd)
	{
	case 1:
		return table[spot_row][spot_col];
		break;
	case 2:
		return table[spot_row][spot_col];
		break;
	case 3:
		return table[spot_row][spot_col];
		break;
	case 4:
		return table[spot_row][spot_col];
		break;
	case 5:
		max = spot_update(table, pre_row, pre_col);
		if (pre_row == post_row)
		{
			for (int i = pre_col; i <= post_col; i++)
			{
				int val = spot_update(table, pre_row, i);
				if(val>max) max = val;
			}
		}
		else
		{
			for (int i = pre_row; i <= post_row; i++)
			{
				int val = spot_update(table, i, pre_col);
				if (val > max) max = val;
			}
		}table[spot_row][spot_col] = max;
		return max;
		break;
	case 6:
		min = spot_update(table, pre_row, pre_col);
		if (pre_row == post_row)
		{
			for (int i = pre_col; i <= post_col; i++)
			{
				int val = spot_update(table, pre_row, i);
				if (val < min) min = val;
			}
		}
		else
		{
			for (int i = pre_row; i <= post_row; i++)
			{
				int val = spot_update(table, i, pre_col);
				if (val < min) min = val;
			}
		}
		return min;
		break;
	case 7:
		sum = 0;
		if (pre_row == post_row)
		{
			for (int i = pre_col; i <= post_col; i++)
			{
				sum = sum + spot_update(table, pre_row, i);
			}
		}
		else
		{
			for (int i = pre_row; i <= post_row; i++)
			{
				sum = sum + spot_update(table, i, pre_col);
			}
		}
		return sum;
		break;
	}

}


void update(int value[MAXR][MAXC]) {
	for (int i = 0; i < g_R; i++)
	{
		for (int j = 0; j < g_C; j++)
		{
			if (table[i][j] == 1000000001)
			{
				table[i][j] = 0;
				value[i][j] = 0;
				printf(" ¤± ");
			}
			else if (table[i][j] > 1000000001)
			{
				value[i][j] = spot_update(table, i, j);
				printf(" %d ", value[i][j]);
			}
			else
			{
				value[i][j] = spot_update(table, i, j);
				printf(" %d ", value[i][j]);
			}
		}
		printf("\n");
	}
}