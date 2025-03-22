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

def areSentencesSimilar(self, sentence1, sentence2):
    """
    :type sentence1: str
    :type sentence2: str
    :rtype: bool
    """
    if len(sentence1) > len(sentence2):
        sentence1, sentence2 = sentence2, sentence1
    count = 0
    for idx in (lambda x:x, lambda x:-1-x):
        for i in xrange(len(sentence1)+1):
            c1 = sentence1[idx(i)] if i != len(sentence1) else ' '
            c2 = sentence2[idx(i)] if i != len(sentence2) else ' '
            if c1 != c2:
                break
            if c1 == ' ':
                count += 1
    return count >= sentence1.count(' ')+1


