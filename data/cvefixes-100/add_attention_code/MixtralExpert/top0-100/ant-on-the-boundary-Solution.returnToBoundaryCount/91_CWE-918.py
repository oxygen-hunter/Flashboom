def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

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


