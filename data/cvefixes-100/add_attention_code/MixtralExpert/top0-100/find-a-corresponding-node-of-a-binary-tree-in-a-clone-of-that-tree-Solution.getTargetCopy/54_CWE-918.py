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

def getTargetCopy(self, original, cloned, target):
    """
    :type original: TreeNode
    :type cloned: TreeNode
    :type target: TreeNode
    :rtype: TreeNode
    """
    def preorder_gen(node):
        stk = [node]
        while stk:
            node = stk.pop()
            if not node:
                continue
            yield node
            stk.append(node.right)
            stk.append(node.left)
        
    for node1, node2 in itertools.izip(preorder_gen(original),
                                       preorder_gen(cloned)):
        if node1 == target:
            return node2


