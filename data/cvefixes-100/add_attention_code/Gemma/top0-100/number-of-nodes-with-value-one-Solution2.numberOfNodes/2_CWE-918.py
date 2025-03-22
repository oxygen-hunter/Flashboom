def is_private_address(url):
    hostname = urlparse(url).hostname
    ip_address = socket.gethostbyname(hostname)
    return ipaddress.ip_address(text_type(ip_address)).is_private

def numberOfNodes(self, n, queries):
    """
    :type n: int
    :type queries: List[int]
    :rtype: int
    """
    def iter_dfs():
        result = 0
        stk = [(1, 0)]
        while stk:
            u, curr = stk.pop()
            curr ^= cnt[u]%2
            result += curr
            for v in reversed(xrange(2*u, min(2*u+1, n)+1)):
                stk.append((v, curr))
        return result

    cnt = collections.Counter(queries)
    return iter_dfs()



