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

def countOfPairs(self, n, x, y):
    """
    :type n: int
    :type x: int
    :type y: int
    :rtype: List[int]
    """
    x, y = x-1, y-1
    if x > y:
        x, y = y, x
    diff = [0]*n
    for i in xrange(n):
        diff[0] += 1+1                                         # i -> two routes begin
        diff[min(abs(i-x), abs(i-y)+1)] += 1                   # i -> x -> y, fork one route at x to y
        diff[min(abs(i-y), abs(i-x)+1)] += 1                   # i -> y -> x, fork one route at y to x
        diff[min(abs(i-0), abs(i-y)+1+abs(x-0))] -= 1          # i -> 0, one route ends
        diff[min(abs(i-(n-1)), abs(i-x)+1+abs(y-(n-1)))] -= 1  # i -> n-1, one route ends
        diff[max(x-i, 0)+max(i-y, 0)+((y-x)+0)//2] -= 1        # i -> x -> ((y-x)+0)//2 <- x, one route ends
        diff[max(x-i, 0)+max(i-y, 0)+((y-x)+1)//2] -= 1        # i -> y -> ((y-x)+1)//2 <- y, one route ends
    for i in xrange(n-1):
        diff[i+1] += diff[i]
    return diff


