def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def winnerOfGame(self, colors):
    """
    :type colors: str
    :rtype: bool
    """
    cnt1 = cnt2 = 0
    for i in xrange(1, len(colors)-1):
        if not (colors[i-1] == colors[i] == colors[i+1]):
            continue
        if colors[i] == 'A':
            cnt1 += 1
        else:
            cnt2 += 1
    return cnt1 > cnt2


