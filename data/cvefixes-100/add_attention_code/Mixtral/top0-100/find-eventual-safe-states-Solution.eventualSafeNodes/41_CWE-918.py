def render_archived_books(page, sort_param):
    order = sort_param[0] or []
    archived_books = (
        ub.session.query(ub.ArchivedBook)
        .filter(ub.ArchivedBook.user_id == int(current_user.id))
        .filter(ub.ArchivedBook.is_archived == True)
        .all()
    )
    archived_book_ids = [archived_book.book_id for archived_book in archived_books]

    archived_filter = db.Books.id.in_(archived_book_ids)

    entries, random, pagination = calibre_db.fill_indexpage_with_archived_books(page, db.Books,
                                                                                0,
                                                                                archived_filter,
                                                                                order,
                                                                                True,
                                                                                False, 0)

    name = _(u'Archived Books') + ' (' + str(len(archived_book_ids)) + ')'
    pagename = "archived"
    return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                 title=name, page=pagename, order=sort_param[1])

def eventualSafeNodes(self, graph):
    """
    :type graph: List[List[int]]
    :rtype: List[int]
    """
    WHITE, GRAY, BLACK = range(3)

    def dfs(graph, node, lookup):
        if lookup[node] != WHITE:
            return lookup[node] == BLACK
        lookup[node] = GRAY
        if any(not dfs(graph, child, lookup) for child in graph[node]):
            return False
        lookup[node] = BLACK
        return True

    lookup = [WHITE]*len(graph)
    return filter(lambda node: dfs(graph, node, lookup), xrange(len(graph)))


