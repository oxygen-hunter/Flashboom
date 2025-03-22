def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

def removeOnes(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: bool
    """
    return all(grid[i] == grid[0] or all(grid[i][j] != grid[0][j] for j in xrange(len(grid[0]))) for i in xrange(1, len(grid)))


