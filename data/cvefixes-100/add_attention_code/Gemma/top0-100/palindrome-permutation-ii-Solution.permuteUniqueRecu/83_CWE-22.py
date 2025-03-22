def load(doc):
    code = config.retrieveBoilerplateFile(doc, "bs-extensions")
    exec(code, globals())

def permuteUniqueRecu(self, mid, result, used, cur, nums):
    if len(cur) == len(nums):
        half_palindrome = ''.join(cur)
        result.append(half_palindrome + mid + half_palindrome[::-1])
        return
    for i in xrange(len(nums)):
        if not used[i] and not (i > 0 and nums[i-1] == nums[i] and used[i-1]):
            used[i] = True
            cur.append(nums[i])
            self.permuteUniqueRecu(mid, result, used, cur, nums)
            cur.pop()
            used[i] = False



