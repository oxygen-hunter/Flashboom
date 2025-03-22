def is_private_address(url):
    hostname = urlparse(url).hostname
    ip_address = socket.gethostbyname(hostname)
    return ipaddress.ip_address(text_type(ip_address)).is_private

def canMakeSquare(self, grid):
    """
    :type grid: List[List[str]]
    :rtype: bool
    """
    N, W = 3, 2
    return any(max(collections.Counter(grid[i+h][j+w] for h in xrange(W) for w in xrange(W)).itervalues()) >= W**2-1
               for i in xrange(N-W+1) for j in xrange(N-W+1))


