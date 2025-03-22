def is_private_address(url):
    hostname = urlparse(url).hostname
    ip_address = socket.gethostbyname(hostname)
    return ipaddress.ip_address(text_type(ip_address)).is_private

def removeInterval(self, intervals, toBeRemoved):
    """
    :type intervals: List[List[int]]
    :type toBeRemoved: List[int]
    :rtype: List[List[int]]
    """
    A, B = toBeRemoved
    return [[x, y] for a, b in intervals
            for x, y in ((a, min(A, b)), (max(a, B), b))
            if x < y]


