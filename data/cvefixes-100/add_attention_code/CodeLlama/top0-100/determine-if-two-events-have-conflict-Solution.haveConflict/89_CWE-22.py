def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def haveConflict(self, event1, event2):
    """
    :type event1: List[str]
    :type event2: List[str]
    :rtype: bool
    """
    return max(event1[0], event2[0]) <= min(event1[1], event2[1])


