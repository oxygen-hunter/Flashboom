def category_list():
    if current_user.check_visibility(constants.SIDEBAR_CATEGORY):
        if current_user.get_view_property('category', 'dir') == 'desc':
            order = db.Tags.name.desc()
            order_no = 0
        else:
            order = db.Tags.name.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Tags, func.count('books_tags_link.book').label('count')) \
            .join(db.books_tags_link).join(db.Books).order_by(order).filter(calibre_db.common_filters()) \
            .group_by(text('books_tags_link.tag')).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Tags.name, 1, 1)).label('char')) \
            .join(db.books_tags_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Tags.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Categories"), page="catlist", data="category", order=order_no)
    else:
        abort(404)

def differByOne(self, dict):
    """
    :type dict: List[str]
    :rtype: bool
    """
    MOD, P = 10**9+7, 113

    hashes = [0]*len(dict)
    for i, word in enumerate(dict):
        for c in word:
            hashes[i] = (P*hashes[i] + (ord(c)-ord('a'))) % MOD

    base = 1
    for p in reversed(xrange(len(dict[0]))):        
        lookup = collections.defaultdict(list)
        for i, word in enumerate(dict):
            new_hash = (hashes[i] - base*(ord(word[p])-ord('a'))) % MOD
            if new_hash in lookup:
                for j in lookup[new_hash]:
                    if dict[j][:p]+dict[j][p+1:] == word[:p]+word[p+1:]:
                        return True
            lookup[new_hash].append(i)
        base = P*base % MOD
    return False


