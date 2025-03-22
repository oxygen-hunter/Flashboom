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

def commonFactors(self, a, b):
    """
    :type a: int
    :type b: int
    :rtype: int
    """
    def gcd(a, b):  # Time: O(log(min(a, b)))
        while b:
            a, b = b, a%b
        return a
    
    g = gcd(a, b)
    result = 0
    x = 1
    while x*x <= g:
        if g%x == 0:
            result += 1 if g//x == x else 2
        x += 1
    return result


