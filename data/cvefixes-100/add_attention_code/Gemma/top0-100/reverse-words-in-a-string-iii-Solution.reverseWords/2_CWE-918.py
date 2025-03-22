def is_private_address(url):
    hostname = urlparse(url).hostname
    ip_address = socket.gethostbyname(hostname)
    return ipaddress.ip_address(text_type(ip_address)).is_private

def reverseWords(self, s):
    """
    :type s: str
    :rtype: str
    """
    def reverse(s, begin, end):
        for i in xrange((end - begin) // 2):
            s[begin + i], s[end - 1 - i] = s[end - 1 - i], s[begin + i]

    s, i = list(s), 0
    for j in xrange(len(s) + 1):
        if j == len(s) or s[j] == ' ':
            reverse(s, i, j)
            i = j + 1
    return "".join(s)



