def replace(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                             str(value)]

    def diffWaysToComputeRecu(left, right):
        if lookup[left][right]:
            return lookup[left][right]
        result = []
        for i in xrange(left, right):
            if input[i] in ops:
                for x in diffWaysToComputeRecu(left, i):
                    for y in diffWaysToComputeRecu(i + 1, right):
                        result.append(ops[input[i]](x, y))

        if not result:
            result = [int(input[left:right])]
        lookup[left][right] = result
        return lookup[left][right]



