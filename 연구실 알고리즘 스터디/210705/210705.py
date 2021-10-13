# HCI랩 알고리즘 스터디 2021.07.05
# 프로그래머스 해시 level2 전화번호 목록

def solution(phone_book):
    phone_book.sort()
    for p1, p2 in zip(phone_book, phone_book[1:]):
        if p2.startswith(p1):
            return False
    return True