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

def validateBinaryTreeNodes(self, n, leftChild, rightChild):
    """
    :type n: int
    :type leftChild: List[int]
    :type rightChild: List[int]
    :rtype: bool
    """
    roots = set(range(n)) - set(leftChild) - set(rightChild)
    if len(roots) != 1:
        return False
    root, = roots
    stk = [root]
    lookup = set([root])
    while stk:
        node = stk.pop()
        for c in (leftChild[node], rightChild[node]):
            if c < 0:
                continue
            if c in lookup:
                return False
            lookup.add(c)
            stk.append(c)
    return len(lookup) == n


