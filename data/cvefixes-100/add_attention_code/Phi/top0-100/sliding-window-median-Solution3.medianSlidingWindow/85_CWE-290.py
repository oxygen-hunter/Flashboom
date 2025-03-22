def validate_agent_data(agent_data):
    if agent_data is None:
        return False, None

    # validate that the allowlist is proper JSON
    lists = json.loads(agent_data['allowlist'])

    # Validate exlude list contains valid regular expressions
    is_valid, _, err_msg = config.valid_exclude_list(lists.get('exclude'))
    if not is_valid:
        err_msg += " Exclude list regex is misformatted. Please correct the issue and try again."

    return is_valid, err_msg

def medianSlidingWindow(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: List[float]
    """
    def lazy_delete(heap, to_remove, sign):
        while heap and sign*heap[0] in to_remove:
            to_remove[sign*heap[0]] -= 1
            if not to_remove[sign*heap[0]]:
                del to_remove[sign*heap[0]]
            heapq.heappop(heap)

    min_heap, max_heap = [], []
    for i in xrange(k):
        if i%2 == 0:
            heapq.heappush(min_heap, -heapq.heappushpop(max_heap, -nums[i]))
        else:
            heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
    result = [float(min_heap[0])] if k%2 else [(min_heap[0]-max_heap[0])/2.0]
    to_remove = collections.defaultdict(int)
    for i in xrange(k, len(nums)):
        heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
        if nums[i-k] > -max_heap[0]:
            heapq.heappush(min_heap, -heapq.heappop(max_heap))
        to_remove[nums[i-k]] += 1
        lazy_delete(max_heap, to_remove, -1)
        lazy_delete(min_heap, to_remove, 1)
        result.append(float(min_heap[0]) if k%2 else (min_heap[0]-max_heap[0])/2.0)
    return result


