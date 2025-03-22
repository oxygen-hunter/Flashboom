def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

def countStrobogrammaticUntil(self, num,  can_start_with_0):
    if can_start_with_0 and num in self.cache:
        return self.cache[num]

    count = 0
    if len(num) == 1:
        for c in ['0', '1', '8']:
            if num[0] >= c:
                count += 1
        self.cache[num] = count
        return count

    for key, val in self.lookup.iteritems():
        if can_start_with_0 or key != '0':
            if num[0] > key:
                if len(num) == 2:  # num is like "21"
                    count += 1
                else:  # num is like "201"
                    count += self.countStrobogrammaticUntil('9' * (len(num) - 2), True)
            elif num[0] == key:
                if len(num) == 2:  # num is like 12".
                    if num[-1] >= val:
                        count += 1
                else:
                    if num[-1] >= val:  # num is like "102".
                        count += self.countStrobogrammaticUntil(self.getMid(num), True)
                    elif (self.getMid(num) != '0' * (len(num) - 2)):  # num is like "110".
                        count += self.countStrobogrammaticUntil(self.getMid(num), True) - \
                                 self.isStrobogrammatic(self.getMid(num))

    if not can_start_with_0: # Sum up each length.
        for i in xrange(len(num) - 1, 0, -1):
            count += self.countStrobogrammaticByLength(i)
    else:
        self.cache[num] = count

    return count



