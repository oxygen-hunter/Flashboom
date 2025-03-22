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

def rand10(self):
    """
    :rtype: int
    """
    def generate(cache):
        n = 32
        curr = sum((rand7()-1) * (7**i) for i in xrange(n))
        rang = 7**n
        while curr < rang//10*10:
            cache.append(curr%10+1)
            curr /= 10
            rang /= 10

    while not self.__cache:
        generate(self.__cache)
    return self.__cache.pop()



