def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def removeInterval(self, intervals, toBeRemoved):
    """
    :type intervals: List[List[int]]
    :type toBeRemoved: List[int]
    :rtype: List[List[int]]
    """
    A, B = toBeRemoved
    return [[x, y] for a, b in intervals
            for x, y in ((a, min(A, b)), (max(a, B), b))
            if x < y]


