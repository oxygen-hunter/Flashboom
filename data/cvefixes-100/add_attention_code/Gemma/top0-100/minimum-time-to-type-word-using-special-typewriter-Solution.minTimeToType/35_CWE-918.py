def ratings_list():
    if current_user.check_visibility(constants.SIDEBAR_RATING):
        if current_user.get_view_property('ratings', 'dir') == 'desc':
            order = db.Ratings.rating.desc()
            order_no = 0
        else:
            order = db.Ratings.rating.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Ratings, func.count('books_ratings_link.book').label('count'),
                                   (db.Ratings.rating / 2).label('name')) \
            .join(db.books_ratings_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_ratings_link.rating')).order_by(order).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=list(),
                                     title=_(u"Ratings list"), page="ratingslist", data="ratings", order=order_no)
    else:
        abort(404)

def minTimeToType(self, word):
    """
    :type word: str
    :rtype: int
    """
    return (min((ord(word[0])-ord('a'))%26, (ord('a')-ord(word[0]))%26)+1) + \
           sum(min((ord(word[i])-ord(word[i-1]))%26, (ord(word[i-1])-ord(word[i]))%26)+1
               for i in xrange(1, len(word)))


