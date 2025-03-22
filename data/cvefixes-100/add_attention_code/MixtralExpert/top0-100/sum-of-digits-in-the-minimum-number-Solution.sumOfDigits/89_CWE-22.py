def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def sumOfDigits(self, A):
    """
    :type A: List[int]
    :rtype: int
    """
    total = sum([int(c) for c in str(min(A))])
    return 1 if total % 2 == 0 else 0


