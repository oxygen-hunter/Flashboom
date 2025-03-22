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

def isEscapePossible(self, blocked, source, target):
    """
    :type blocked: List[List[int]]
    :type source: List[int]
    :type target: List[int]
    :rtype: bool
    """
    R, C = 10**6, 10**6
    directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

    def bfs(blocks, source, target):
        max_area_surrounded_by_blocks = len(blocks)*(len(blocks)-1)//2
        lookup = set([source])
        if len(lookup) > max_area_surrounded_by_blocks:
            return True
        q = collections.deque([source])
        while q:
            source = q.popleft()
            if source == target:
                return True
            for direction in directions:
                nr, nc = source[0]+direction[0], source[1]+direction[1]
                if not ((0 <= nr < R) and
                        (0 <= nc < C) and 
                        (nr, nc) not in lookup and
                        (nr, nc) not in blocks):
                    continue
                lookup.add((nr, nc))
                if len(lookup) > max_area_surrounded_by_blocks:
                    return True
                q.append((nr, nc))
        return False
    
    return bfs(set(map(tuple, blocked)), tuple(source), tuple(target)) and \
           bfs(set(map(tuple, blocked)), tuple(target), tuple(source))


