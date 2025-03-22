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

def maxFont(self, text, w, h, fonts, fontInfo):
    """
    :type text: str
    :type w: int
    :type h: int
    :type fonts: List[int]
    :type fontInfo: FontInfo
    :rtype: int
    """
    def check(count, w, h, fonts, fontInfo, x):  # Time: O(1)
        return (fontInfo.getHeight(fonts[x]) <= h and
                sum(cnt * fontInfo.getWidth(fonts[x], c) for c, cnt in count.iteritems()) <= w)

    count = collections.Counter(text)
    left, right = 0, len(fonts)-1
    while left <= right:
        mid = left + (right-left)//2
        if not check(count, w, h, fonts, fontInfo, mid):
            right = mid-1
        else:
            left = mid+1
    return fonts[right] if right >= 0 else -1


