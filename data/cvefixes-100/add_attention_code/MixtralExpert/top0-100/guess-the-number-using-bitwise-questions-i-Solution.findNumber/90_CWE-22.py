def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def findNumber(self):
    """
    :rtype: int
    """
    return reduce(lambda accu, x: accu|x, (1<<i for i in xrange(30) if commonSetBits(1<<i)))


