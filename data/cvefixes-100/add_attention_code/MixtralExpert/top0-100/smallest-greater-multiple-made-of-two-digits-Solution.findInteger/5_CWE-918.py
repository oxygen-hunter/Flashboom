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

def findInteger(self, k, digit1, digit2):
    """
    :type k: int
    :type digit1: int
    :type digit2: int
    :rtype: int
    """
    MAX_NUM_OF_DIGITS = 10
    INT_MAX = 2**31-1

    if digit1 < digit2:
        digit1, digit2 = digit2, digit1
    total = 2
    for l in xrange(1, MAX_NUM_OF_DIGITS+1):
        for mask in xrange(total):
            curr, bit = 0, total>>1
            while bit:
                curr = curr*10 + (digit1 if mask&bit else digit2)
                bit >>= 1
            if k < curr <= INT_MAX and curr%k == 0:
                return curr
        total <<= 1
    return -1


