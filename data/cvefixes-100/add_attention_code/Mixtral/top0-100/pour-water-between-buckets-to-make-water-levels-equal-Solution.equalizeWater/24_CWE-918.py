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

def equalizeWater(self, buckets, loss):
    """
    :type buckets: List[int]
    :type loss: int
    :rtype: float
    """
    def check(buckets, rate, x):
        return sum(b-x for b in buckets if b-x > 0)*rate >= sum(x-b for b in buckets if x-b > 0)

    EPS = 1e-5
    rate = (100-loss)/100.0
    left, right = float(min(buckets)), float(sum(buckets))/len(buckets)
    while right-left > EPS:
        mid = left + (right-left)/2
        if not check(buckets, rate, mid):
            right = mid
        else:
            left = mid
    return left


