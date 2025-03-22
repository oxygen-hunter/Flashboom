def render_prepare_search_form(cc):
    # prepare data for search-form
    tags = calibre_db.session.query(db.Tags)\
        .join(db.books_tags_link)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(text('books_tags_link.tag'))\
        .order_by(db.Tags.name).all()
    series = calibre_db.session.query(db.Series)\
        .join(db.books_series_link)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(text('books_series_link.series'))\
        .order_by(db.Series.name)\
        .filter(calibre_db.common_filters()).all()
    shelves = ub.session.query(ub.Shelf)\
        .filter(or_(ub.Shelf.is_public == 1, ub.Shelf.user_id == int(current_user.id)))\
        .order_by(ub.Shelf.name).all()
    extensions = calibre_db.session.query(db.Data)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(db.Data.format)\
        .order_by(db.Data.format).all()
    if current_user.filter_language() == u"all":
        languages = calibre_db.speaking_language()
    else:
        languages = None
    return render_title_template('search_form.html', tags=tags, languages=languages, extensions=extensions,
                                 series=series,shelves=shelves, title=_(u"Advanced Search"), cc=cc, page="advsearch")

def checkMove(self, board, rMove, cMove, color):
    """
    :type board: List[List[str]]
    :type rMove: int
    :type cMove: int
    :type color: str
    :rtype: bool
    """
    def check(board, color, r, c, dr, dc):
        l = 2
        while 0 <= r < len(board) and 0 <= c < len(board[0]) and board[r][c] != '.':
            if board[r][c] == color:
                return l >= 3    
            r += dr
            c += dc
            l += 1
        return False

    directions = [(0, -1), (0, 1), (-1, 0), (1, 0),
                  (-1, -1), (1, -1), (-1, 1), (1, 1)]
    for dr, dc in directions:
        r, c = rMove+dr, cMove+dc
        if check(board, color, r, c, dr, dc):
            return True
    return False


