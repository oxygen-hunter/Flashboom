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

def kSimilarity(self, A, B):
    """
    :type A: str
    :type B: str
    :rtype: int
    """
    def neighbors(s, B):
        for i, c in enumerate(s):
            if c != B[i]:
                break
        t = list(s)
        for j in xrange(i+1, len(s)):
            if t[j] == B[i]:
                t[i], t[j] = t[j], t[i]
                yield "".join(t)
                t[j], t[i] = t[i], t[j]

    q = collections.deque([A])
    lookup = set()
    result = 0
    while q:
        for _ in xrange(len(q)):
            s = q.popleft()
            if s == B:
                return result
            for t in neighbors(s, B):
                if t not in lookup:
                    lookup.add(t)
                    q.append(t)
        result += 1



