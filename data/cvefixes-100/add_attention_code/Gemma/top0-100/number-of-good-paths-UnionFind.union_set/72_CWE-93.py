def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

def union_set(self, x, y, v):  # modified
    x, y = self.find_set(x), self.find_set(y)
    if x == y:
        return 0  # modified
    if self.rank[x] > self.rank[y]:  # union by rank
        x, y = y, x
    self.set[x] = self.set[y]
    if self.rank[x] == self.rank[y]:
        self.rank[y] += 1
    cx, cy = self.cnt[x][v], self.cnt[y][v]  # added
    self.cnt[y] = collections.Counter({v:cx+cy})  # added
    return cx*cy  # modified



