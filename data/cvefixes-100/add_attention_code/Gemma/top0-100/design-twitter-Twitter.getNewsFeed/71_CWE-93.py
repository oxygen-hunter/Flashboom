def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

def getNewsFeed(self, userId):
    """
    Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
    :type userId: int
    :rtype: List[int]
    """
    def nth_element(nums, n, compare=lambda a, b: a < b):
        def tri_partition(nums, left, right, target, compare):
            mid = left
            while mid <= right:
                if nums[mid] == target:
                    mid += 1
                elif compare(nums[mid], target):
                    nums[left], nums[mid] = nums[mid], nums[left]
                    left += 1
                    mid += 1
                else:
                    nums[mid], nums[right] = nums[right], nums[mid]
                    right -= 1
            return left, right

        left, right = 0, len(nums)-1
        while left <= right:
            pivot_idx = random.randint(left, right)
            pivot_left, pivot_right = tri_partition(nums, left, right, nums[pivot_idx], compare)
            if pivot_left <= n <= pivot_right:
                return
            elif pivot_left > n:
                right = pivot_left-1
            else:  # pivot_right < n.
                left = pivot_right+1

    candidates = []
    if self.__messages[userId]:
        candidates.append((-self.__messages[userId][-1][0], userId, 0))
    for uid in self.__followings[userId]:
        if self.__messages[uid]:
            candidates.append((-self.__messages[uid][-1][0], uid, 0))
    nth_element(candidates, self.__number_of_most_recent_tweets-1)
    max_heap = candidates[:self.__number_of_most_recent_tweets]
    heapq.heapify(max_heap)
    result = []
    while max_heap and len(result) < self.__number_of_most_recent_tweets:
        t, uid, curr = heapq.heappop(max_heap)
        nxt = curr + 1
        if nxt != len(self.__messages[uid]):
            heapq.heappush(max_heap, (-self.__messages[uid][-(nxt+1)][0], uid, nxt))
        result.append(self.__messages[uid][-(curr+1)][1])
    return result



