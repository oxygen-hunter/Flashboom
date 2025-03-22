def add_security_headers(resp):
    resp.headers['Content-Security-Policy'] = "default-src 'self'" + ''.join([' '+host for host in config.config_trustedhosts.strip().split(',')]) + " 'unsafe-inline' 'unsafe-eval'; font-src 'self' data:; img-src 'self' data:"
    if request.endpoint == "editbook.edit_book" or config.config_use_google_drive:
        resp.headers['Content-Security-Policy'] += " *"
    elif request.endpoint == "web.read_book":
        resp.headers['Content-Security-Policy'] += " blob:;style-src-elem 'self' blob: 'unsafe-inline';"
    resp.headers['X-Content-Type-Options'] = 'nosniff'
    resp.headers['X-Frame-Options'] = 'SAMEORIGIN'
    resp.headers['X-XSS-Protection'] = '1; mode=block'
    resp.headers['Strict-Transport-Security'] = 'max-age=31536000;'
    return resp

def wantsToEat(self, philosopher, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork):
    """
    :type philosopher: int
    :type pickLeftFork: method
    :type pickRightFork: method
    :type eat: method
    :type putLeftFork: method
    :type putRightFork: method
    :rtype: void
    """
    left, right = philosopher, (philosopher+4)%5
    first, second = left, right
    if  philosopher%2 == 0:
        first, second = left, right
    else:
        first, second = right, left

    with self._l[first]:
        with self._l[second]:
            pickLeftFork()
            pickRightFork()
            eat()
            putLeftFork()
            putRightFork()


