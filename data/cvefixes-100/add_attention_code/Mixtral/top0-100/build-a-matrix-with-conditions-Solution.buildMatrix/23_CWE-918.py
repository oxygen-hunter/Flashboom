def language_overview():
    if current_user.check_visibility(constants.SIDEBAR_LANGUAGE) and current_user.filter_language() == u"all":
        order_no = 0 if current_user.get_view_property('language', 'dir') == 'desc' else 1
        charlist = list()
        languages = calibre_db.speaking_language(reverse_order=not order_no, with_count=True)
        for lang in languages:
            upper_lang = lang[0].name[0].upper()
            if upper_lang not in charlist:
                charlist.append(upper_lang)
        return render_title_template('languages.html', languages=languages,
                                     charlist=charlist, title=_(u"Languages"), page="langlist",
                                     data="language", order=order_no)
    else:
        abort(404)

def buildMatrix(self, k, rowConditions, colConditions):
    """
    :type k: int
    :type rowConditions: List[List[int]]
    :type colConditions: List[List[int]]
    :rtype: List[List[int]]
    """
    def topological_sort(conditions):
        adj = [[] for _ in xrange(k)]
        in_degree = [0]*k
        for u, v in conditions:
            u -= 1
            v -= 1
            adj[u].append(v)
            in_degree[v] += 1
        result = []
        q = [u for u in xrange(k) if not in_degree[u]]
        while q:
            new_q = []
            for u in q:
                result.append(u)
                for v in adj[u]:
                    in_degree[v] -= 1
                    if in_degree[v]:
                        continue
                    new_q.append(v)
            q = new_q
        return result

    row_order = topological_sort(rowConditions)
    if len(row_order) != k:
        return []
    col_order = topological_sort(colConditions)
    if len(col_order) != k:
        return []
    row_idx = {x:i for i, x in enumerate(row_order)}
    col_idx = {x:i for i, x in enumerate(col_order)}
    result = [[0]*k for _ in xrange(k)]
    for i in xrange(k):
        result[row_idx[i]][col_idx[i]] = i+1
    return result


