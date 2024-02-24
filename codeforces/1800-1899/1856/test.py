
a = [0, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1]


def work(l, r):
    # 求[l, r] 的逆序对数
    if l == r:
        return 0
    mid = (l + r) // 2
    res = work(l, mid) + work(mid + 1, r)
    i, j = l, mid + 1
    while i <= mid and j <= r:
        if a[i] > a[j]:
            res += mid - i + 1
            j += 1
        else:
            i += 1
    return res


print(work(1, 5))