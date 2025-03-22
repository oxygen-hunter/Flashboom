def add_objects(db_book_object, db_object, db_session, db_type, add_elements):
    changed = False
    if db_type == 'languages':
        db_filter = db_object.lang_code
    elif db_type == 'custom':
        db_filter = db_object.value
    else:
        db_filter = db_object.name
    for add_element in add_elements:
        # check if a element with that name exists
        db_element = db_session.query(db_object).filter(db_filter == add_element).first()
        # if no element is found add it
        if db_type == 'author':
            new_element = db_object(add_element, helper.get_sorted_author(add_element.replace('|', ',')), "")
        elif db_type == 'series':
            new_element = db_object(add_element, add_element)
        elif db_type == 'custom':
            new_element = db_object(value=add_element)
        elif db_type == 'publisher':
            new_element = db_object(add_element, None)
        else:  # db_type should be tag or language
            new_element = db_object(add_element)
        if db_element is None:
            changed = True
            db_session.add(new_element)
            db_book_object.append(new_element)
        else:
            db_element = create_objects_for_addition(db_element, add_element, db_type)
            changed = True
            # add element to book
            changed = True
            db_book_object.append(db_element)
    return changed

def findGoodStrings(self, n, s1, s2, evil):
    """
    :type n: int
    :type s1: str
    :type s2: str
    :type evil: str
    :rtype: int
    """
    MOD = 10**9+7
    def getPrefix(pattern):
        prefix = [-1]*len(pattern)
        j = -1
        for i in xrange(1, len(pattern)):
            while j != -1 and pattern[j+1] != pattern[i]:
                j = prefix[j]
            if pattern[j+1] == pattern[i]:
                j += 1
            prefix[i] = j
        return prefix

    prefix = getPrefix(evil)
    dp = [[[[0]*len(evil) for _ in xrange(2)] for _ in xrange(2)] for _ in xrange(2)]
    dp[0][0][0][0] = 1
    for i in xrange(n):
        dp[(i+1)%2] = [[[0]*len(evil) for _ in xrange(2)] for _ in xrange(2)]
        for j in xrange(2):
            for k in xrange(2):
                min_c = 'a' if j else s1[i]
                max_c = 'z' if k else s2[i]
                for l in xrange(len(evil)):
                    if not dp[i%2][j][k][l]:
                        continue
                    for c in xrange(ord(min_c)-ord('a'), ord(max_c)-ord('a')+1):
                        c = chr(c+ord('a'))
                        m = l-1
                        while m != -1 and evil[m+1] != c:
                            m = prefix[m]
                        if evil[m+1] == c:
                            m += 1
                        if m+1 == len(evil):
                            continue
                        dp[(i+1)%2][j or (s1[i] != c)][k or (s2[i] != c)][m+1] = \
                            (dp[(i+1)%2][j or (s1[i] != c)][k or (s2[i] != c)][m+1] + dp[i%2][j][k][l]) % MOD
    result = 0
    for j in xrange(2):
        for k in xrange(2):
            for l in xrange(len(evil)):
                result = (result + dp[n%2][j][k][l]) % MOD
    return result


