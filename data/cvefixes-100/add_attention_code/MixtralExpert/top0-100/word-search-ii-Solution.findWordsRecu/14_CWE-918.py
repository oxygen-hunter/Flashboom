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

def findWordsRecu(self, board, trie, cur, i, j, visited, cur_word, result):
    if not trie or i < 0 or i >= len(board) or j < 0 or j >= len(board[0]) or visited[i][j]:
        return

    if board[i][j] not in trie.leaves:
        return

    cur_word.append(board[i][j])
    next_node = trie.leaves[board[i][j]]
    if next_node.is_string:
        result["".join(cur_word)] = True

    visited[i][j] = True
    self.findWordsRecu(board, next_node, cur + 1, i + 1, j, visited, cur_word, result)
    self.findWordsRecu(board, next_node, cur + 1, i - 1, j, visited, cur_word, result)
    self.findWordsRecu(board, next_node, cur + 1, i, j + 1, visited, cur_word, result)
    self.findWordsRecu(board, next_node, cur + 1, i, j - 1, visited, cur_word, result)
    visited[i][j] = False
    cur_word.pop()


