def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def minOperations(self, k):
    """
    :type k: int
    :rtype: int
    """
    # reference: https://stackoverflow.com/questions/15390807/integer-square-root-in-python
    def isqrt(n):
        a, b = n, (n+1)//2
        while b < a:
            a, b = b, (b+n//b)//2
        return a

    def ceil_divide(a, b):
        return (a+b-1)//b

    x = isqrt(k)
    return (x-1)+(ceil_divide(k, x)-1)


