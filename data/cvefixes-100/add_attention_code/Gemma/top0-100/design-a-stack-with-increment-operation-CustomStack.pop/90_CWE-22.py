def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def pop(self):
    """
    :rtype: int
    """
    if not self.__stk:
        return -1
    x, inc = self.__stk.pop()
    if self.__stk:
        self.__stk[-1][1] += inc
    return x + inc



