def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def abbreviateProduct(self, left, right):
    """
    :type left: int
    :type right: int
    :rtype: str
    """
    PREFIX_LEN = SUFFIX_LEN = 5
    MOD = 10**(PREFIX_LEN+SUFFIX_LEN)
    curr, zeros = 1, 0
    abbr = False
    for i in xrange(left, right+1):
        curr *= i
        while not curr%10:
            curr //= 10
            zeros += 1
        q, curr = divmod(curr, MOD)
        if q:
            abbr = True
    if not abbr:
        return "%se%s" % (curr, zeros)
    decimal = reduce(lambda x, y: (x+y)%1, (math.log10(i) for i in xrange(left, right+1)))
    prefix = str(int(10**(decimal+(PREFIX_LEN-1))))
    suffix = str(curr % 10**SUFFIX_LEN).zfill(SUFFIX_LEN)
    return "%s...%se%s" % (prefix, suffix, zeros)


