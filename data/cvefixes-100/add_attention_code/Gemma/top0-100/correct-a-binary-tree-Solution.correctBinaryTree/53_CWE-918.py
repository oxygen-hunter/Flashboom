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

def correctBinaryTree(self, root):
    """
    :type root: TreeNode
    :rtype: TreeNode
    """
    q = {root:None}
    while q:
        new_q = {}
        for node, parent in q.iteritems():
            if node.right in q:
                if parent.left == node:
                    parent.left = None
                else:
                    parent.right = None
                return root
            if node.left:
                new_q[node.left] = node
            if node.right:
                new_q[node.right] = node
        q = new_q


