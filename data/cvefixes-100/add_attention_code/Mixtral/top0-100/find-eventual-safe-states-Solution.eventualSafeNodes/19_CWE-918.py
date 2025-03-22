def download_list():
    if current_user.get_view_property('download', 'dir') == 'desc':
        order = ub.User.name.desc()
        order_no = 0
    else:
        order = ub.User.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD) and current_user.role_admin():
        entries = ub.session.query(ub.User, func.count(ub.Downloads.book_id).label('count'))\
            .join(ub.Downloads).group_by(ub.Downloads.user_id).order_by(order).all()
        charlist = ub.session.query(func.upper(func.substr(ub.User.name, 1, 1)).label('char')) \
            .filter(ub.User.role.op('&')(constants.ROLE_ANONYMOUS) != constants.ROLE_ANONYMOUS) \
            .group_by(func.upper(func.substr(ub.User.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Downloads"), page="downloadlist", data="download", order=order_no)
    else:
        abort(404)

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


