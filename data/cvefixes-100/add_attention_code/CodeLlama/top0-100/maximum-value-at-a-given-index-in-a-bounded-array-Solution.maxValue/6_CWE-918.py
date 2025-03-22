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

def maxValue(self, n, index, maxSum):
    """
    :type n: int
    :type index: int
    :type maxSum: int
    :rtype: int
    """
    def check(n, index, maxSum, x):
        y = max(x-index, 0)
        total = (x+y)*(x-y+1)//2
        y = max(x-((n-1)-index), 0)
        total += (x+y)*(x-y+1)//2
        return total-x <= maxSum

    maxSum -= n
    left, right = 0, maxSum
    while left <= right:
        mid = left + (right-left)//2
        if not check(n, index, maxSum, mid):
            right = mid-1
        else:
            left = mid+1
    return 1+right


