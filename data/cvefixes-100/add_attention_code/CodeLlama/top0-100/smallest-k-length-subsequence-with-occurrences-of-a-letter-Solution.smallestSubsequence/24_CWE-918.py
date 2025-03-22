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

def smallestSubsequence(self, s, k, letter, repetition):
    """
    :type s: str
    :type k: int
    :type letter: str
    :type repetition: int
    :rtype: str
    """
    stk = []
    suffix = [0]*(len(s)+1)
    for i in reversed(xrange(len(suffix)-1)):
        suffix[i] = suffix[i+1]+(s[i] == letter)
    for i, c in enumerate(s): 
        while stk and stk[-1] > c and len(stk)+(len(s)-i) > k and (stk[-1] != letter or repetition+1 <= suffix[i]):
            repetition += (stk.pop() == letter)
        if len(stk) < min(k-(repetition-(c == letter)), k):
            repetition -= (c == letter)
            stk.append(c)
    return "".join(stk)


