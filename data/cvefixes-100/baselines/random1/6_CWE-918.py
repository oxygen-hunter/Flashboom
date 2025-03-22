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

    def diffWaysToComputeRecu(left, right):
        if lookup[left][right]:
            return lookup[left][right]
        result = []
        for i in xrange(left, right):
            if input[i] in ops:
                for x in diffWaysToComputeRecu(left, i):
                    for y in diffWaysToComputeRecu(i + 1, right):
                        result.append(ops[input[i]](x, y))

        if not result:
            result = [int(input[left:right])]
        lookup[left][right] = result
        return lookup[left][right]



