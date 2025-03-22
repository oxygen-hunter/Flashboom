def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def check(self, nums):
    """
    :type nums: List[int]
    :rtype: bool
    """
    count = 0
    for i in xrange(len(nums)):
        if nums[i] > nums[(i+1)%len(nums)]:
            count += 1
            if count > 1:
                return False
    return True


