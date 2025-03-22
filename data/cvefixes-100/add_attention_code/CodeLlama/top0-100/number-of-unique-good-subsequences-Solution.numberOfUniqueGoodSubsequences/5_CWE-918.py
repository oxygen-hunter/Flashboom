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

def numberOfUniqueGoodSubsequences(self, binary):
    """
    :type binary: str
    :rtype: int
    """
    MOD = 10**9+7
    ends0, ends1 = 0, 0
    has_zero = False
    for b in binary:
        if b == '1':
            ends1 = (ends0+ends1+1)%MOD  # curr subsequences end with 1 is all prev distinct subsequences appended by 1 and plus "1"
        else:
            ends0 = (ends0+ends1)%MOD  # curr subsequences end with 0 is all prev distinct subsequences appended by 0 and don't plus "0"
            has_zero = True
    return (ends0+ends1+int(has_zero))%MOD  # add "0" if has_zero


