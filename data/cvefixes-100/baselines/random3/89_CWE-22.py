def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def subarraySum(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    result = 0
    accumulated_sum = 0
    lookup = collections.defaultdict(int)
    lookup[0] += 1
    for num in nums:
        accumulated_sum += num
        result += lookup[accumulated_sum - k]
        lookup[accumulated_sum] += 1
    return result



