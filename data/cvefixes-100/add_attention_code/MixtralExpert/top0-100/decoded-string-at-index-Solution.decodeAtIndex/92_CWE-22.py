def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def decodeAtIndex(self, S, K):
    """
    :type S: str
    :type K: int
    :rtype: str
    """
    i = 0
    for c in S:
        if c.isdigit():
            i *= int(c)
        else:
            i += 1

    for c in reversed(S):
        K %= i
        if K == 0 and c.isalpha():
            return c

        if c.isdigit():
            i /= int(c)
        else:
            i -= 1



