def load(doc):
    code = config.retrieveBoilerplateFile(doc, "bs-extensions")
    exec(code, globals())

def isArmstrong(self, N):
    """
    :type N: int
    :rtype: bool
    """
    n_str = str(N)
    return sum(int(i)**len(n_str) for i in n_str) == N


