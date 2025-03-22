def author_list():
    if current_user.check_visibility(constants.SIDEBAR_AUTHOR):
        if current_user.get_view_property('author', 'dir') == 'desc':
            order = db.Authors.sort.desc()
            order_no = 0
        else:
            order = db.Authors.sort.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Authors, func.count('books_authors_link.book').label('count')) \
            .join(db.books_authors_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_authors_link.author')).order_by(order).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Authors.sort, 1, 1)).label('char')) \
            .join(db.books_authors_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Authors.sort, 1, 1))).all()
        # If not creating a copy, readonly databases can not display authornames with "|" in it as changing the name
        # starts a change session
        autor_copy = copy.deepcopy(entries)
        for entry in autor_copy:
            entry.Authors.name = entry.Authors.name.replace('|', ',')
        return render_title_template('list.html', entries=autor_copy, folder='web.books_list', charlist=charlist,
                                     title=u"Authors", page="authorlist", data='author', order=order_no)
    else:
        abort(404)

def minimumCost(self, sentence, k):
    """
    :type sentence: str
    :type k: int
    :rtype: int
    """
    word_lens = []
    j = 0
    for i in xrange(len(sentence)+1):
        if i != len(sentence) and sentence[i] != ' ':
            continue
        word_lens.append(i-j)
        j = i+1
    dp = [float("inf")]*(1+(len(word_lens)-1))  # dp[i]: min cost of the first i word_lens where i in [0, len(words)-1]
    dp[0] = 0
    for i in xrange(1, (len(word_lens)-1)+1):
        total = word_lens[i-1]
        for j in reversed(xrange(i)):
            dp[i] = min(dp[i], dp[j] + (k-total)**2)
            if j-1 < 0:
                continue
            total += (word_lens[j-1]+1)
            if total > k:
                break
    i, total = len(word_lens)-1, -1
    while i >= 0 and total + (word_lens[i]+1) <= k:  # find max i s.t. the length of the last line > k
        total += (word_lens[i]+1)
        i -= 1
    return min(dp[j] for j in xrange(i+1, len(dp)))


