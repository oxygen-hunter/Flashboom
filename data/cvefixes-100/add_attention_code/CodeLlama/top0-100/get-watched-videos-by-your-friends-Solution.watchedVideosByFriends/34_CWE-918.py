def publisher_list():
    if current_user.get_view_property('publisher', 'dir') == 'desc':
        order = db.Publishers.name.desc()
        order_no = 0
    else:
        order = db.Publishers.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_PUBLISHER):
        entries = calibre_db.session.query(db.Publishers, func.count('books_publishers_link.book').label('count')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_publishers_link.publisher')).order_by(order).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Publishers.name, 1, 1)).label('char')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Publishers.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Publishers"), page="publisherlist", data="publisher", order=order_no)
    else:
        abort(404)

def watchedVideosByFriends(self, watchedVideos, friends, id, level):
    """
    :type watchedVideos: List[List[str]]
    :type friends: List[List[int]]
    :type id: int
    :type level: int
    :rtype: List[str]
    """
    curr_level, lookup = set([id]), set([id])
    for _ in xrange(level):
        curr_level = set(j for i in curr_level for j in friends[i] if j not in lookup)
        lookup |= curr_level
    count = collections.Counter([v for i in curr_level for v in watchedVideos[i]])
    return sorted(count.keys(), key=lambda x: (count[x], x))


