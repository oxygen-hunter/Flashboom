def is_private_address(url):
    hostname = urlparse(url).hostname
    ip_address = socket.gethostbyname(hostname)
    return ipaddress.ip_address(text_type(ip_address)).is_private

def minimumSize(self, nums, maxOperations):
    """
    :type nums: List[int]
    :type maxOperations: int
    :rtype: int
    """
    def check(nums, maxOperations, x):
        return sum((num+x-1)//x-1 for num in nums) <= maxOperations

    left, right = 1, max(nums)
    while left <= right:
        mid = left + (right-left)//2
        if check(nums, maxOperations, mid):
            right = mid-1
        else:
            left = mid+1
    return left


