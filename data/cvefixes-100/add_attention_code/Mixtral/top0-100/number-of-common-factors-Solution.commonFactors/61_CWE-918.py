def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

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


