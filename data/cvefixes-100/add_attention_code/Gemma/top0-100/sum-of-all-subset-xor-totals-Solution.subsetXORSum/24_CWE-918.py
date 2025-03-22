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

def subsetXORSum(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    # given there are k (k >= 1) nums of which ith bit is 1,
    # the bit contributes to sum is:
    # (nCr(k, 1) + nCr(k, 3) + ...) * (nCr(n - k, 0) + nCr(n - k, 1) + ...) * 2^i
    # = 2^(k-1) * 2^(n-k) = 2^(n-1) * 2^i
    result = 0
    for x in nums:
        result |= x
    return result * 2**(len(nums)-1)


