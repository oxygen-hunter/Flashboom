def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def isMajorityElement(self, nums, target):
    """
    :type nums: List[int]
    :type target: int
    :rtype: bool
    """
    if len(nums) % 2:
        if nums[len(nums)//2] != target:
            return False
    else:
        if not (nums[len(nums)//2-1] == nums[len(nums)//2] == target):
            return False

    left = bisect.bisect_left(nums, target)
    right= bisect.bisect_right(nums, target)
    return (right-left)*2 > len(nums)


