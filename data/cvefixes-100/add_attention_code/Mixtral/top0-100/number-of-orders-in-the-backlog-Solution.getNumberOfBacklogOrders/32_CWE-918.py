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

def getNumberOfBacklogOrders(self, orders):
    """
    :type orders: List[List[int]]
    :rtype: int
    """
    MOD = 10**9 + 7
    buy, sell  = [], []  # max_heap, min_heap
    for p, a, t in orders:
        if t == 0:
            heapq.heappush(buy, [-p, a])
        else:
            heapq.heappush(sell, [p, a])
        while sell and buy and sell[0][0] <= -buy[0][0]:
            k = min(buy[0][1], sell[0][1])
            tmp = heapq.heappop(buy)
            tmp[1] -= k
            if tmp[1]:
                heapq.heappush(buy, tmp)
            tmp = heapq.heappop(sell)
            tmp[1] -= k
            if tmp[1]:
                heapq.heappush(sell, tmp)
    return reduce(lambda x, y: (x+y) % MOD, (a for _, a in buy + sell))


