def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def haveConflict(self, event1, event2):
    """
    :type event1: List[str]
    :type event2: List[str]
    :rtype: bool
    """
    return max(event1[0], event2[0]) <= min(event1[1], event2[1])


