async def send_transaction(self, account, to, selector_name, calldata, nonce=None, max_fee=0):
    return await self.send_transactions(account, [(to, selector_name, calldata)], nonce, max_fee)

def summaryRanges(self, nums):
    ranges = []
    if not nums:
        return ranges

    start, end = nums[0], nums[0]
    for i in xrange(1, len(nums) + 1):
        if i < len(nums) and nums[i] == end + 1:
            end = nums[i]
        else:
            interval = str(start)
            if start != end:
                interval += "->" + str(end)
            ranges.append(interval)
            if i < len(nums):
                start = end = nums[i]

    return ranges



