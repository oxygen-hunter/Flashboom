def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

def query(self, L, R):  # Time: O(logN), Space: O(N)
    def push(x):
        n = 2**self.H
        while n != 1:
            y = x // n
            if self.lazy[y] is not None:
                self.__apply(y*2, self.lazy[y])
                self.__apply(y*2 + 1, self.lazy[y])
                self.lazy[y] = None
            n //= 2

    result = None
    if L > R:
        return result

    L += self.N
    R += self.N
    push(L)
    push(R)
    while L <= R:
        if L & 1:  # is right child
            result = self.query_fn(result, self.tree[L])
            L += 1
        if R & 1 == 0:  # is left child
            result = self.query_fn(result, self.tree[R])
            R -= 1
        L //= 2
        R //= 2
    return result



