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

def kthSmallestProduct(self, nums1, nums2, k):
    """
    :type nums1: List[int]
    :type nums2: List[int]
    :type k: int
    :rtype: int
    """
    def check(nums1, nums2, k, neg_cnt, target):
        cnt = 0
        left, right = 0, len(nums2)-1
        direction = reversed if target >= 0 else lambda x: x
        for i in direction(xrange(neg_cnt)):
            while left < len(nums2) and nums1[i]*nums2[left] > target:
                left += 1
            cnt += (len(nums2)-1)-left+1
        direction = (lambda x: x) if target >= 0 else reversed
        for i in direction(xrange(neg_cnt, len(nums1))): 
            if nums1[i] == 0: 
                if target >= 0:
                    cnt += len(nums2)
                continue
            while right >= 0 and nums1[i]*nums2[right] > target:
                right -= 1
            cnt += right-0+1
        return cnt >= k

    neg_cnt = sum(x < 0 for x in nums1)
    left = min(nums1[i]*nums2[j] for i in (0, -1) for j in (0, -1))
    right = max(nums1[i]*nums2[j] for i in (0, -1) for j in (0, -1))
    while left <= right:
        mid = left + (right-left)//2
        if check(nums1, nums2, k, neg_cnt, mid):
            right = mid-1
        else:
            left = mid+1
    return left


