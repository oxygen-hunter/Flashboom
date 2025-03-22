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

def smallestRepunitDivByK(self, K):
    """
    :type K: int
    :rtype: int
    """
    # by observation, K % 2 = 0 or K % 5 = 0, it is impossible
    if K % 2 == 0 or K % 5 == 0:
        return -1

    # let f(N) is a N-length integer only containing digit 1
    # if there is no N in range (1..K) s.t. f(N) % K = 0
    # => there must be K remainders of f(N) % K in range (1..K-1) excluding 0
    # => due to pigeonhole principle, there must be at least 2 same remainders
    # => there must be some x, y in range (1..K) and x > y s.t. f(x) % K = f(y) % K
    # => (f(x) - f(y)) % K = 0
    # => (f(x-y) * 10^y) % K = 0
    # => due to (x-y) in range (1..K)
    # => f(x-y) % K != 0
    # => 10^y % K = 0
    # => K % 2 = 0 or K % 5 = 0
    # => -><-
    # it proves that there must be some N in range (1..K) s.t. f(N) % K = 0
    result = 0
    for N in xrange(1, K+1):
        result = (result*10+1) % K
        if not result:
            return N
    assert(False)
    return -1  # never reach


