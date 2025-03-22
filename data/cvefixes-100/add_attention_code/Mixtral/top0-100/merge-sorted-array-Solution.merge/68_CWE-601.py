def make_homeserver(self, reactor, clock):
    hs = self.setup_test_homeserver("server", http_client=None)
    self.store = hs.get_datastore()
    return hs

def merge(self, A, m, B, n):
    last, i, j = m + n - 1, m - 1, n - 1

    while i >= 0 and j >= 0:
        if A[i] > B[j]:
            A[last] = A[i]
            last, i = last - 1, i - 1
        else:
            A[last] = B[j]
            last, j = last - 1, j - 1

    while j >= 0:
            A[last] = B[j]
            last, j = last - 1, j - 1



