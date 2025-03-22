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

def largestMagicSquare(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    def get_sum(prefix, a, b):
        return prefix[b+1]-prefix[a]

    def check(grid, prefix_row, prefix_col, l, i, j):
        diag, anti_diag = 0, 0
        for d in xrange(l):
            diag += grid[i+d][j+d]
            anti_diag += grid[i+d][j+l-1-d]
        if diag != anti_diag:
            return False
        for ni in xrange(i, i+l):
            if diag != get_sum(prefix_row[ni], j, j+l-1):
                return False
        for nj in xrange(j, j+l):
            if diag != get_sum(prefix_col[nj], i, i+l-1):
                return False  
        return True

    prefix_row = [[0]*(len(grid[0])+1) for _ in xrange(len(grid))]
    prefix_col = [[0]*(len(grid)+1) for _ in xrange(len(grid[0]))]
    for i in xrange(len(grid)):
        for j in xrange(len(grid[0])):
            prefix_row[i][j+1] = prefix_row[i][j] + grid[i][j]
            prefix_col[j][i+1] = prefix_col[j][i] + grid[i][j]
    for l in reversed(xrange(1, min(len(grid), len(grid[0]))+1)):
        for i in xrange(len(grid)-(l-1)):
            for j in xrange(len(grid[0])-(l-1)):
                if check(grid, prefix_row, prefix_col, l, i, j):
                    return l
    return 1


