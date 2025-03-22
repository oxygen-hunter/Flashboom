def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def add(self, num):
    """
    :type num: int
    :rtype: None
    """
    if not num:
        self.__accu = [1]
        return
    self.__accu.append(self.__accu[-1]*num)             



