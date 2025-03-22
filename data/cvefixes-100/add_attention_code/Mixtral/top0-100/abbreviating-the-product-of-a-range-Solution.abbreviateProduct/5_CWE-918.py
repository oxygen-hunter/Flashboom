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

def abbreviateProduct(self, left, right):
    """
    :type left: int
    :type right: int
    :rtype: str
    """
    PREFIX_LEN = SUFFIX_LEN = 5
    MOD = 10**(PREFIX_LEN+SUFFIX_LEN)
    curr, zeros = 1, 0
    abbr = False
    for i in xrange(left, right+1):
        curr *= i
        while not curr%10:
            curr //= 10
            zeros += 1
        q, curr = divmod(curr, MOD)
        if q:
            abbr = True
    if not abbr:
        return "%se%s" % (curr, zeros)
    decimal = reduce(lambda x, y: (x+y)%1, (math.log10(i) for i in xrange(left, right+1)))
    prefix = str(int(10**(decimal+(PREFIX_LEN-1))))
    suffix = str(curr % 10**SUFFIX_LEN).zfill(SUFFIX_LEN)
    return "%s...%se%s" % (prefix, suffix, zeros)


