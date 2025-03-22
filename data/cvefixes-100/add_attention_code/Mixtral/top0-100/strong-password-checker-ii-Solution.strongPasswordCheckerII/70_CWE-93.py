def _hkey(s):
    return s.title().replace('_', '-')

def strongPasswordCheckerII(self, password):
    """
    :type password: str
    :rtype: bool
    """
    SPECIAL = set("!@#$%^&*()-+")
    return (len(password) >= 8 and
            any(c.islower() for c in password) and
            any(c.isupper() for c in password) and
            any(c.isdigit() for c in password) and
            any(c in SPECIAL for c in password) and
            all(password[i] != password[i+1] for i in xrange(len(password)-1)))


