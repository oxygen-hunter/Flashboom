def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

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



