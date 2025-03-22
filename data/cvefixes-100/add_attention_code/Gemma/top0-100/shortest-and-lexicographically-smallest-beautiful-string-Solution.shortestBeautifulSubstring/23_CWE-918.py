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

def shortestBeautifulSubstring(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: str
    """
    def check(r1, r2):
        if r1[1]-r1[0]+1 > r2[1]-r2[0]+1:
            return False
        if r1[1]-r1[0]+1 < r2[1]-r2[0]+1:
            return True
        for i, j in itertools.izip(xrange(r1[0], r1[1]+1), xrange(r2[0], r2[1]+1)):
            if s[i] != s[j]:
                return s[i] < s[j]
        return False

    result = []
    left = curr = 0
    for right in xrange(len(s)):
        curr += s[right] == '1'
        while curr == k+1:
            curr -= s[left] == '1'
            left += 1
        while left < len(s) and s[left] == '0':
            left += 1
        if curr == k:
            if not result or check([left, right], result):
                result = [left, right]
    return s[result[0]:result[1]+1] if result else ""


