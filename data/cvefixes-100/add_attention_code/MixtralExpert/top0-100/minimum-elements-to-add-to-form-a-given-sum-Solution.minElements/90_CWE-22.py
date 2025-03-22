def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def minElements(self, nums, limit, goal):
    """
    :type nums: List[int]
    :type limit: int
    :type goal: int
    :rtype: int
    """
    return (abs(sum(nums)-goal) + (limit-1))//limit


