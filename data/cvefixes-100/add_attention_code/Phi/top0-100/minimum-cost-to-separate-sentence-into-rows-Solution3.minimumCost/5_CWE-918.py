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

def minimumCost(self, sentence, k):
    """
    :type sentence: str
    :type k: int
    :rtype: int
    """
    word_lens = []
    j = 0
    for i in xrange(len(sentence)+1):
        if i != len(sentence) and sentence[i] != ' ':
            continue
        word_lens.append(i-j)
        j = i+1
    dp = [float("inf")]*(1+(len(word_lens)-1))  # dp[i]: min cost of the first i word_lens where i in [0, len(words)-1]
    dp[0] = 0
    for i in xrange(1, (len(word_lens)-1)+1):
        total = word_lens[i-1]
        for j in reversed(xrange(i)):
            dp[i] = min(dp[i], dp[j] + (k-total)**2)
            if j-1 < 0:
                continue
            total += (word_lens[j-1]+1)
            if total > k:
                break
    i, total = len(word_lens)-1, -1
    while i >= 0 and total + (word_lens[i]+1) <= k:  # find max i s.t. the length of the last line > k
        total += (word_lens[i]+1)
        i -= 1
    return min(dp[j] for j in xrange(i+1, len(dp)))


