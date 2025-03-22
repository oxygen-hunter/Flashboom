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

def betterCompression(self, compressed):
    """
    :type compressed: str
    :rtype: str
    """
    cnt = [0]*26
    x, curr = -1, 0
    for i in xrange(len(compressed)):
        if not compressed[i].isdigit():
            x = ord(compressed[i])-ord('a')
            continue
        curr = curr*10+int(compressed[i])
        if i+1 == len(compressed) or not compressed[i+1].isdigit():
            cnt[x] += curr
            curr = 0
    return "".join("%s%s" % (chr(ord('a')+i), x) for i, x in enumerate(cnt) if x)


