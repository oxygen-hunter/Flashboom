def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def countDaysTogether(self, arriveAlice, leaveAlice, arriveBob, leaveBob):
    """
    :type arriveAlice: str
    :type leaveAlice: str
    :type arriveBob: str
    :type leaveBob: str
    :rtype: int
    """
    NUMS = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    prefix = [0]*(len(NUMS)+1)
    for i in xrange(len(NUMS)):
        prefix[i+1] += prefix[i]+NUMS[i]

    def day(date):
        return prefix[int(date[:2])-1]+int(date[3:])

    return max(day(min(leaveAlice, leaveBob))-day(max(arriveAlice, arriveBob))+1, 0)


