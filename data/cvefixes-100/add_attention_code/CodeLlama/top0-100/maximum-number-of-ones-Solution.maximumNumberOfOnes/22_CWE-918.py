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

def maximumNumberOfOnes(self, width, height, sideLength, maxOnes):
    """
    :type width: int
    :type height: int
    :type sideLength: int
    :type maxOnes: int
    :rtype: int
    """
    if width < height:
        width, height = height, width

    # 1. split matrix by SxS tiles
    # 2. split each SxS tile into four parts
    #    (r, c), (r, S-c), (S-r, c), (S-r, S-c)
    # 3. for each count of tile part in matrix is
    #    (R+1)*(C+1), (R+1)*C, R*(C+1), R*C (already in descending order)
    # 4. fill one into matrix by tile part of which count is in descending order
    #    until number of ones in a tile comes to maxOnes
    # 
    # ps. area of a tile and its count in matrix are as follows:
    #
    #  |<---- c ---->|<-- S-c -->|
    #  ^             |           |
    #  |             |           |
    #  r (R+1)*(C+1) |  (R+1)*C  |
    #  |             |           |
    #  v             |           |
    #  ---------------------------
    #  ^             |           |
    #  |             |           |
    #  S-r  R*(C+1)  |   R*C     |
    #  |             |           |
    #  v             |           |
    #  ---------------------------
    #

    R, r = divmod(height, sideLength)
    C, c = divmod(width, sideLength)
    assert(R <= C)
    area_counts = [(r*c, (R+1)*(C+1)), \
                   (r*(sideLength-c), (R+1)*C), \
                   ((sideLength-r)*c, R*(C+1)), \
                   ((sideLength-r)*(sideLength-c), R*C)]
    result = 0
    for area, count in area_counts:
        area = min(maxOnes, area)
        result += count*area
        maxOnes -= area
        if not maxOnes:
            break
    return result


