def is_private_address(url):
    hostname = urlparse(url).hostname
    ip_address = socket.gethostbyname(hostname)
    return ipaddress.ip_address(text_type(ip_address)).is_private

def minMoves2(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def kthElement(nums, k):
        def PartitionAroundPivot(left, right, pivot_idx, nums):
            pivot_value = nums[pivot_idx]
            new_pivot_idx = left
            nums[pivot_idx], nums[right] = nums[right], nums[pivot_idx]
            for i in xrange(left, right):
                if nums[i] > pivot_value:
                    nums[i], nums[new_pivot_idx] = nums[new_pivot_idx], nums[i]
                    new_pivot_idx += 1

            nums[right], nums[new_pivot_idx] = nums[new_pivot_idx], nums[right]
            return new_pivot_idx

        left, right = 0, len(nums) - 1
        while left <= right:
            pivot_idx = randint(left, right)
            new_pivot_idx = PartitionAroundPivot(left, right, pivot_idx, nums)
            if new_pivot_idx == k:
                return nums[new_pivot_idx]
            elif new_pivot_idx > k:
                right = new_pivot_idx - 1
            else:  # new_pivot_idx < k.
                left = new_pivot_idx + 1

    median = kthElement(nums, len(nums)//2)
    return sum(abs(num - median) for num in nums)



