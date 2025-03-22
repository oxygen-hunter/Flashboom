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

def twoEditWords(self, queries, dictionary):
    """
    :type queries: List[str]
    :type dictionary: List[str]
    :rtype: List[str]
    """
    MOD = (1<<64)-59  # largest 64-bit prime
    BASE = 113
    POW = [1]
    def add(a, b):
        return (a+b)%MOD

    def mult(a, b):
        return (a*b)%MOD

    def pow(i):
        while not (i < len(POW)):
            POW.append(mult(POW[-1], BASE))
        return POW[i]

    lookup = set()
    for w in dictionary:
        h = reduce(lambda h, i: add(h, mult(ord(w[i])-ord('a'), pow(i))), xrange(len(w)), 0)
        for i, c in enumerate(w):
            for x in string.ascii_lowercase:
                if x == c:
                    continue
                lookup.add(add(h, mult(ord(x)-ord(c), pow(i))))
    result = []
    for w in queries:
        h = reduce(lambda h, i: add(h, mult(ord(w[i])-ord('a'), pow(i))), xrange(len(w)), 0)
        for i, c in enumerate(w):
            for x in string.ascii_lowercase:
                if x == c:
                    continue
                if add(h, mult(ord(x)-ord(c), pow(i))) in lookup:
                    break
            else:
                continue
            result.append(w)
            break
    return result



