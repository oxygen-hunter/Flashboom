def render_search_results(term, offset=None, order=None, limit=None):
    join = db.books_series_link, db.Books.id == db.books_series_link.c.book, db.Series
    entries, result_count, pagination = calibre_db.get_search_results(term,
                                                                      offset,
                                                                      order,
                                                                      limit,
                                                                      False,
                                                                      config.config_read_column,
                                                                      *join)
    return render_title_template('search.html',
                                 searchterm=term,
                                 pagination=pagination,
                                 query=term,
                                 adv_searchterm=term,
                                 entries=entries,
                                 result_count=result_count,
                                 title=_(u"Search"),
                                 page="search",
                                 order=order[1])

def __init__(self, root):
    """
    :type root: TreeNode
    """
    def dfs(node, v, lookup):
        if not node:
            return
        node.val = v    
        lookup.add(v)
        dfs(node.left, 2*v+1, lookup)
        dfs(node.right, 2*v+2, lookup)

    self.__lookup = set()
    dfs(root, 0, self.__lookup)



