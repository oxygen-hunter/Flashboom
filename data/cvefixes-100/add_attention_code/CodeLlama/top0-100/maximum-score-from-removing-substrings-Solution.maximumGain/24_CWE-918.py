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

def maximumGain(self, s, x, y):
    """
    :type s: str
    :type x: int
    :type y: int
    :rtype: int
    """
    def score(s, a, x):
        i = result = 0
        for j in xrange(len(s)):
            s[i] = s[j]
            i += 1
            if i >= 2 and s[i-2:i] == a:
                i -= 2
                result += x
        s[:] = s[:i]
        return result
            
    s, a, b = list(s), list("ab"), list("ba")
    if x < y:
        x, y = y, x
        a, b = b, a
    return score(s, a, x) + score(s, b, y)


