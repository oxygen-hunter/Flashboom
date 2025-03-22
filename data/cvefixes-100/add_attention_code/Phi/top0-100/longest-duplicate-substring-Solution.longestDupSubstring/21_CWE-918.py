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

def longestDupSubstring(self, S):
    """
    :type S: str
    :rtype: str
    """
    M = 10**9+7
    D = 26

    def check(S, L):
        p = pow(D, L, M)
        curr = reduce(lambda x, y: (D*x+ord(y)-ord('a')) % M, S[:L], 0)
        lookup = collections.defaultdict(list)
        lookup[curr].append(L-1)
        for i in xrange(L, len(S)):
            curr = ((D*curr) % M + ord(S[i])-ord('a') -
                    ((ord(S[i-L])-ord('a'))*p) % M) % M
            if curr in lookup:
                for j in lookup[curr]:  # check if string is the same when hash is the same
                    if S[j-L+1:j+1] == S[i-L+1:i+1]:
                        return i-L+1
            lookup[curr].append(i)
        return 0

    left, right = 1, len(S)-1
    while left <= right:
        mid = left + (right-left)//2
        if not check(S, mid):
            right = mid-1
        else:
            left = mid+1
    result = check(S, right)
    return S[result:result + right]


