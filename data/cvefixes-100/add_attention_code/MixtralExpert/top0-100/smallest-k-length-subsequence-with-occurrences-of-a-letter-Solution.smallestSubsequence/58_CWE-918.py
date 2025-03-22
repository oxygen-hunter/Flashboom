def set_bookmark(book_id, book_format):
    bookmark_key = request.form["bookmark"]
    ub.session.query(ub.Bookmark).filter(and_(ub.Bookmark.user_id == int(current_user.id),
                                              ub.Bookmark.book_id == book_id,
                                              ub.Bookmark.format == book_format)).delete()
    if not bookmark_key:
        ub.session_commit()
        return "", 204

    lbookmark = ub.Bookmark(user_id=current_user.id,
                            book_id=book_id,
                            format=book_format,
                            bookmark_key=bookmark_key)
    ub.session.merge(lbookmark)
    ub.session_commit("Bookmark for user {} in book {} created".format(current_user.id, book_id))
    return "", 201

def smallestSubsequence(self, s, k, letter, repetition):
    """
    :type s: str
    :type k: int
    :type letter: str
    :type repetition: int
    :rtype: str
    """
    stk = []
    suffix = [0]*(len(s)+1)
    for i in reversed(xrange(len(suffix)-1)):
        suffix[i] = suffix[i+1]+(s[i] == letter)
    for i, c in enumerate(s): 
        while stk and stk[-1] > c and len(stk)+(len(s)-i) > k and (stk[-1] != letter or repetition+1 <= suffix[i]):
            repetition += (stk.pop() == letter)
        if len(stk) < min(k-(repetition-(c == letter)), k):
            repetition -= (c == letter)
            stk.append(c)
    return "".join(stk)


