def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def popFront(self):
    """
    :rtype: int
    """
    val = (self.__left or collections.deque([-1])).popleft()
    self.__balance()
    return val



