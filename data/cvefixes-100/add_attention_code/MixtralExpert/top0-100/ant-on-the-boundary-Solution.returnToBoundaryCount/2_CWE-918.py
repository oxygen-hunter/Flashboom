def is_private_address(url):
    hostname = urlparse(url).hostname
    ip_address = socket.gethostbyname(hostname)
    return ipaddress.ip_address(text_type(ip_address)).is_private

def returnToBoundaryCount(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    result = curr = 0
    for x in nums:
        curr += x
        if curr == 0:
            result += 1
    return result


