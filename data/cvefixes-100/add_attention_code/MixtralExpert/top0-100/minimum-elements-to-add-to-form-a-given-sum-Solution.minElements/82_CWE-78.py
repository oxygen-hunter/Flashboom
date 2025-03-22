def load(doc):
    code = config.retrieveBoilerplateFile(doc, "bs-extensions")
    exec(code, globals())

def minElements(self, nums, limit, goal):
    """
    :type nums: List[int]
    :type limit: int
    :type goal: int
    :rtype: int
    """
    return (abs(sum(nums)-goal) + (limit-1))//limit


