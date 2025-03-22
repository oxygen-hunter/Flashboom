def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

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


