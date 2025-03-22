def extend_search_term(searchterm,
                       author_name,
                       book_title,
                       publisher,
                       pub_start,
                       pub_end,
                       tags,
                       rating_high,
                       rating_low,
                       read_status,
                       ):
    searchterm.extend((author_name.replace('|', ','), book_title, publisher))
    if pub_start:
        try:
            searchterm.extend([_(u"Published after ") +
                               format_date(datetime.strptime(pub_start, "%Y-%m-%d"),
                                           format='medium', locale=get_locale())])
        except ValueError:
            pub_start = u""
    if pub_end:
        try:
            searchterm.extend([_(u"Published before ") +
                               format_date(datetime.strptime(pub_end, "%Y-%m-%d"),
                                           format='medium', locale=get_locale())])
        except ValueError:
            pub_end = u""
    elements = {'tag': db.Tags, 'serie':db.Series, 'shelf':ub.Shelf}
    for key, db_element in elements.items():
        tag_names = calibre_db.session.query(db_element).filter(db_element.id.in_(tags['include_' + key])).all()
        searchterm.extend(tag.name for tag in tag_names)
        tag_names = calibre_db.session.query(db_element).filter(db_element.id.in_(tags['exclude_' + key])).all()
        searchterm.extend(tag.name for tag in tag_names)
    language_names = calibre_db.session.query(db.Languages). \
        filter(db.Languages.id.in_(tags['include_language'])).all()
    if language_names:
        language_names = calibre_db.speaking_language(language_names)
    searchterm.extend(language.name for language in language_names)
    language_names = calibre_db.session.query(db.Languages). \
        filter(db.Languages.id.in_(tags['exclude_language'])).all()
    if language_names:
        language_names = calibre_db.speaking_language(language_names)
    searchterm.extend(language.name for language in language_names)
    if rating_high:
        searchterm.extend([_(u"Rating <= %(rating)s", rating=rating_high)])
    if rating_low:
        searchterm.extend([_(u"Rating >= %(rating)s", rating=rating_low)])
    if read_status:
        searchterm.extend([_(u"Read Status = %(status)s", status=read_status)])
    searchterm.extend(ext for ext in tags['include_extension'])
    searchterm.extend(ext for ext in tags['exclude_extension'])
    # handle custom columns
    searchterm = " + ".join(filter(None, searchterm))
    return searchterm, pub_start, pub_end

def earliestAndLatest(self, n, firstPlayer, secondPlayer):
    """
    :type n: int
    :type firstPlayer: int
    :type secondPlayer: int
    :rtype: List[int]
    """
    def memoization(t, l, r, lookup):
        # t: total number of players,
        # l: number of players left to the nearest top2 player,
        # r: number of players right to the nearest top2 player
        if (t, l, r) not in lookup:
            if l == r:
                return (1, 1)
            if l > r:  # make sure l <= r
                l, r, = r, l
            result = [float("inf"), 0]
            for i in xrange(l+1):
                l_win_cnt, l_lose_cnt, nt, pair_cnt = i+1, l-i, (t+1)//2, t//2
                min_j = max(l_lose_cnt, r-(pair_cnt-l_lose_cnt))  # j >= l_lose_cnt and j >= r-(pair_cnt-l_lose_cnt)
                max_j = min(r-l_win_cnt, (nt-l_win_cnt)-1)  # j <= r-l_win_cnt and j <= (nt-l_win_cnt)-1
                for j in xrange(min_j, max_j+1):
                    tmp = memoization(nt, i, j, lookup)
                    result = min(result[0], tmp[0]+1), max(result[1], tmp[1]+1)
            lookup[t, l, r] = result
        return lookup[t, l, r]
    
    return memoization(n, firstPlayer-1, n-secondPlayer, {})


