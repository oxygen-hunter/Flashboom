def render_search_results(term, offset=None, order=None, limit=None):
    join = db.books_series_link, db.Books.id == db.books_series_link.c.book, db.Series
    entries, result_count, pagination = calibre_db.get_search_results(term,
                                                                      offset,
                                                                      order,
                                                                      limit,
                                                                      False,
                                                                      config.config_read_column,
                                                                      *join)
    return render_title_template('search.html',
                                 searchterm=term,
                                 pagination=pagination,
                                 query=term,
                                 adv_searchterm=term,
                                 entries=entries,
                                 result_count=result_count,
                                 title=_(u"Search"),
                                 page="search",
                                 order=order[1])

def mergeArrays(self, nums1, nums2):
    """
    :type nums1: List[List[int]]
    :type nums2: List[List[int]]
    :rtype: List[List[int]]
    """
    result = []
    i = j = 0
    while i < len(nums1) or j < len(nums2):
        if j == len(nums2) or (i < len(nums1) and nums1[i][0] < nums2[j][0]):
            if result and result[-1][0] == nums1[i][0]:
                result[-1][1] += nums1[i][1]
            else:
                result.append(nums1[i])
            i += 1
        else:
            if result and result[-1][0] == nums2[j][0]:
                result[-1][1] += nums2[j][1]
            else:
                result.append(nums2[j])
            j += 1
    return result


