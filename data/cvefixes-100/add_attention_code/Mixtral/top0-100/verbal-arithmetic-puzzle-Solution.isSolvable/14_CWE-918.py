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

def isSolvable(self, words, result):
    """
    :type words: List[str]
    :type result: str
    :rtype: bool
    """
    def backtracking(words, result, i, j, carry, lookup, used):
        if j == len(result):
            return carry == 0

        if i != len(words):
            if j >= len(words[i]) or words[i][j] in lookup:
                return backtracking(words, result, i+1, j, carry, lookup, used)     
            for val in xrange(10):
                if val in used or (val == 0 and j == len(words[i])-1):
                    continue
                lookup[words[i][j]] = val
                used.add(val)
                if backtracking(words, result, i+1, j, carry, lookup, used):
                    return True
                used.remove(val)
                del lookup[words[i][j]]
            return False

        carry, val = divmod(carry + sum(lookup[w[j]] for w in words if j < len(w)), 10)
        if result[j] in lookup:
            return val == lookup[result[j]] and \
                   backtracking(words, result, 0, j+1, carry, lookup, used)
        if val in used or (val == 0 and j == len(result)-1):
            return False
        lookup[result[j]] = val
        used.add(val)
        if backtracking(words, result, 0, j+1, carry, lookup, used):
            return True
        used.remove(val)
        del lookup[result[j]]
        return False
    
    return backtracking([w[::-1] for w in words], result[::-1], 0, 0, 0, {}, set())


