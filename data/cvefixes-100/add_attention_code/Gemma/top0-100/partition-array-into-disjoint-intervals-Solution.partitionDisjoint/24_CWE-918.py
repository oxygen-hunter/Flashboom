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

def partitionDisjoint(self, A):
    """
    :type A: List[int]
    :rtype: int
    """
    B = A[:]
    for i in reversed(xrange(len(A)-1)):
        B[i] = min(B[i], B[i+1])
    p_max = 0
    for i in xrange(1, len(A)):
        p_max = max(p_max, A[i-1])
        if p_max <= B[i]:
            return i



