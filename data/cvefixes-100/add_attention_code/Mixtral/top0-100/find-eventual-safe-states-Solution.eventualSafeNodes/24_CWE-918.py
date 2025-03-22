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


