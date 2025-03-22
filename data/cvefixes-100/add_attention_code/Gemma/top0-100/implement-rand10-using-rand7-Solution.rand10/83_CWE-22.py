def load(doc):
    code = config.retrieveBoilerplateFile(doc, "bs-extensions")
    exec(code, globals())

def rand10(self):
    """
    :rtype: int
    """
    def generate(cache):
        n = 32
        curr = sum((rand7()-1) * (7**i) for i in xrange(n))
        rang = 7**n
        while curr < rang//10*10:
            cache.append(curr%10+1)
            curr /= 10
            rang /= 10

    while not self.__cache:
        generate(self.__cache)
    return self.__cache.pop()



