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

def canMakeSquare(self, grid):
    """
    :type grid: List[List[str]]
    :rtype: bool
    """
    N, W = 3, 2
    return any(max(collections.Counter(grid[i+h][j+w] for h in xrange(W) for w in xrange(W)).itervalues()) >= W**2-1
               for i in xrange(N-W+1) for j in xrange(N-W+1))


