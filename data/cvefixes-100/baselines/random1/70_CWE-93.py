def _hkey(s):
    return s.title().replace('_', '-')

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



