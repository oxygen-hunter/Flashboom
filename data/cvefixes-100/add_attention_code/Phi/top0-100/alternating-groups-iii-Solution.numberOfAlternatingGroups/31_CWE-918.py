def profile():
    languages = calibre_db.speaking_language()
    translations = babel.list_translations() + [LC('en')]
    kobo_support = feature_support['kobo'] and config.config_kobo_sync
    if feature_support['oauth'] and config.config_login_type == 2:
        oauth_status = get_oauth_status()
        local_oauth_check = oauth_check
    else:
        oauth_status = None
        local_oauth_check = {}

    if request.method == "POST":
        change_profile(kobo_support, local_oauth_check, oauth_status, translations, languages)
    return render_title_template("user_edit.html",
                                 translations=translations,
                                 profile=1,
                                 languages=languages,
                                 content=current_user,
                                 kobo_support=kobo_support,
                                 title=_(u"%(name)s's profile", name=current_user.name),
                                 page="me",
                                 registered_oauth=local_oauth_check,
                                 oauth_status=oauth_status)

def numberOfAlternatingGroups(self, colors, queries):
    """
    :type colors: List[int]
    :type queries: List[List[int]]
    :rtype: List[int]
    """
    class BIT(object):  # 0-indexed.
        def __init__(self, n):
            self.__bit = [0]*(n+1)

        def add(self, i, val):
            i += 1
            while i < len(self.__bit):
                self.__bit[i] += val
                i += (i & -i)

        def query(self, i):
            i += 1
            ret = 0
            while i > 0:
                ret += self.__bit[i]
                i -= (i & -i)
            return ret

    def update(i, d):
        if d == +1:
            sl.add(i)
            if len(sl) == 1:
                bit1.add(n, +1)
                bit2.add(n, +n)
        curr = sl.index(i)
        prv, nxt = (curr-1)%len(sl), (curr+1)%len(sl)
        if len(sl) != 1:
            l = (sl[nxt]-sl[prv]-1)%n+1
            bit1.add(l, d*(-1))
            bit2.add(l, d*(-l))
            l = (sl[curr]-sl[prv])%n
            bit1.add(l, d*(+1))
            bit2.add(l, d*(+l))
            l = (sl[nxt]-sl[curr])%n
            bit1.add(l, d*(+1))
            bit2.add(l, d*(+l))
        if d == -1:
            if len(sl) == 1:
                bit1.add(n, -1)
                bit2.add(n, -n)
            sl.pop(curr)

    n = len(colors)
    sl = SortedList()
    bit1, bit2 = BIT(n+1), BIT(n+1)
    for i in xrange(n):
        if colors[i] == colors[(i+1)%n]:
            update(i, +1)
    result = []
    for q in queries:
        if q[0] == 1:
            l = q[1]
            result.append((bit2.query(n)-bit2.query(l-1))-
                          (l-1)*(bit1.query(n)-bit1.query(l-1)) if sl else n)
            continue
        _, i, c = q
        if colors[i] == c:
            continue      
        colors[i] = c          
        update((i-1)%n, +1 if colors[i] == colors[(i-1)%n] else -1) 
        update(i, +1 if colors[i] == colors[(i+1)%n] else -1)
    return result


