#define _CRT_SECURE_NO_WARNINGS
#define N 4

#include <stdio.h>
typedef struct {
    int hit;
    int miss;
} Result;


// API
extern Result query(int guess[]);

static int candidates[5040][5];
static int sample[N];
static int sample_c[10];

static bool isValid(int guess[]) {
	int guess_c[10];

	for (int count = 0; count < 10; ++count) guess_c[count] = 0;
	for (int idx = 0; idx < N; ++idx) {
		if (guess[idx] < 0 || guess[idx] >= 10 || guess_c[guess[idx]] > 0) return false;
		guess_c[guess[idx]]++;
	}
	return true;
}



Result query_sample (int candidates[]) {
	Result result;

	if (!isValid(candidates)) {
		result.hit = -1;
		result.miss = -1;
		return result;
	}

	result.hit = 0;
	result.miss = 0;

	for (int idx = 0; idx < N; ++idx)
		if (candidates[idx] == sample[idx])
			result.hit++;
		else if (sample_c[candidates[idx]] > 0)
			result.miss++;

	return result;
}
void initialize(int guess[]) {
	for (int count = 0; count < 10; ++count) sample_c[count] = 0;
	for (int idx = 0; idx < N; ++idx) {
		sample[idx] = guess[idx];
		sample_c[sample[idx]]++;
	}
}

void doUserImplementation(int guess[]) {
    // Implement a user's implementation function
    //
    // The array of guess[] is a return array that
    // is your guess for what digits[] would be.
	

	//while(result.hit != 4){}
	// 후보리스트 생성
	int candidate_idx = 0;
	for (int i1 = 0; i1 < 10; i1++) {
		for (int i2 = 0; i2 < 10; i2++) {
			if (i1 != i2) {
				for (int i3 = 0; i3 < 10; i3++)
				{
					if (i3 != i1 && i3 != i2) {
						for (int i4 = 0; i4 < 10; i4++)
						{
							if (i4 != i1 && i4 != i2 && i4 != i3) {
								candidates[candidate_idx][0] = i1;
								candidates[candidate_idx][1] = i2;
								candidates[candidate_idx][2] = i3;
								candidates[candidate_idx][3] = i4;
								candidate_idx++;
							}
						}
					}
				}
			}
		}
	}
	//넣어볼랜덤수 생성
	while (1) {
		for (int i = 0; i < candidate_idx; i++) {
			if (candidates[i][0] != -1) {
				guess[0] = candidates[i][0];
				guess[1] = candidates[i][1];
				guess[2] = candidates[i][2];
				guess[3] = candidates[i][3];
				break;
			}
		}
		
		initialize(guess);

		Result result = query(guess);
		//printf("\n hit : %d miss : %d \n", result.hit, result.miss);

		for (int i = 0; i < candidate_idx; i++)
		{
			Result result_sample = query_sample(candidates[i]);
			if (result_sample.hit == result.hit && result_sample.miss == result.miss) continue;
			else candidates[i][0] = -1;
		}

		//printf("=========================cnt : %d================================\n",cnt);
		int candidate_cnt = 0;
		for (int i = 0; i < candidate_idx; i++)
		{
			if (candidates[i][0] != -1)
			{
				//printf("%d : %d%d%d%d  ", candidate_cnt, candidates[i][0], candidates[i][1], candidates[i][2], candidates[i][3]);
				candidate_cnt++;
			}
		}
	

		//printf("\nreal hit : %d real miss : %d\n", result.hit, result.miss);
		//printf("guess : %d%d%d%d", guess[0], guess[1], guess[2], guess[3]);
		//printf("sample : %d%d%d%d", sample[0], sample[1], sample[2], sample[3]);
		//printf("candidate_cnt : %d", candidate_cnt);
		if (result.hit == 4) break;
	}

}
