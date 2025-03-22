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

def betterCompression(self, compressed):
    """
    :type compressed: str
    :rtype: str
    """
    cnt = [0]*26
    x, curr = -1, 0
    for i in xrange(len(compressed)):
        if not compressed[i].isdigit():
            x = ord(compressed[i])-ord('a')
            continue
        curr = curr*10+int(compressed[i])
        if i+1 == len(compressed) or not compressed[i+1].isdigit():
            cnt[x] += curr
            curr = 0
    return "".join("%s%s" % (chr(ord('a')+i), x) for i, x in enumerate(cnt) if x)


