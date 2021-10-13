# HCI랩 알고리즘 스터디 2021.07.08
# 프로그래머스 스택/큐 level2 프린터

def solution(bridge_length, weight, truck_weights):
    time = 0
    q = [0] * bridge_length
    
    while q:
        time += 1
        q.pop(0)
        if truck_weights:
            if sum(q) + truck_weights[0] <= weight:
                q.append(truck_weights.pop(0))
            else:
                q.append(0)
    
    return time