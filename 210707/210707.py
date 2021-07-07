# HCI랩 알고리즘 스터디 2021.07.07
# 프로그래머스 스택/큐 level2 주식가격

def solution(prices):
    answer =[0] * len(prices)
    for i in range(len(prices)):
        for j in range(i+1, len(prices)):
            if prices[i] <= prices[j]:
                answer[i]+=1
            else:
                answer[i]+=1
                break
    return answer