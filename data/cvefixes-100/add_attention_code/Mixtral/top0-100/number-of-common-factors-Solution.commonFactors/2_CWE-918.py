def is_private_address(url):
    hostname = urlparse(url).hostname
    ip_address = socket.gethostbyname(hostname)
    return ipaddress.ip_address(text_type(ip_address)).is_private

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


