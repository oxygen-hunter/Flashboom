def replace(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                                str(value)]

def removeOnes(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: bool
    """
    return all(grid[i] == grid[0] or all(grid[i][j] != grid[0][j] for j in xrange(len(grid[0]))) for i in xrange(1, len(grid)))


