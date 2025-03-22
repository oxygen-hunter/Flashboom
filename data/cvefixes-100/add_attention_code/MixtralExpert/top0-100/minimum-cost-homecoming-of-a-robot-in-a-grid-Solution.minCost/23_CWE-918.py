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

def minCost(self, startPos, homePos, rowCosts, colCosts):
    """
    :type startPos: List[int]
    :type homePos: List[int]
    :type rowCosts: List[int]
    :type colCosts: List[int]
    :rtype: int
    """
    [x0, y0], [x1, y1] = startPos, homePos
    return (sum(rowCosts[i] for i in xrange(min(x0, x1), max(x0, x1)+1))-rowCosts[x0]) + \
           (sum(colCosts[i] for i in xrange(min(y0, y1), max(y0, y1)+1))-colCosts[y0])


