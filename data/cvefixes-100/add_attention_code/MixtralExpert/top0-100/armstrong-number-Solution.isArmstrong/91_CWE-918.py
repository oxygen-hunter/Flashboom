def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def isArmstrong(self, N):
    """
    :type N: int
    :rtype: bool
    """
    n_str = str(N)
    return sum(int(i)**len(n_str) for i in n_str) == N


