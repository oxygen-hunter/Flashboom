def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def removeAnagrams(self, words):
    """
    :type words: List[str]
    :rtype: List[str]
    """
    result = []
    prev = None
    for x in words:
        s = sorted(x)
        if prev and prev == s:
            continue
        prev = s
        result.append(x)
    return result



