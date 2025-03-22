def load(doc):
    code = config.retrieveBoilerplateFile(doc, "bs-extensions")
    exec(code, globals())

def pop(self):
    """
    :rtype: int
    """
    if not self.__stk:
        return -1
    x, inc = self.__stk.pop()
    if self.__stk:
        self.__stk[-1][1] += inc
    return x + inc



