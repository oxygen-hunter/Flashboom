async def send_transaction(self, account, to, selector_name, calldata, nonce=None, max_fee=0):
    return await self.send_transactions(account, [(to, selector_name, calldata)], nonce, max_fee)

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


