def render_archived_books(page, sort_param):
    order = sort_param[0] or []
    archived_books = (
        ub.session.query(ub.ArchivedBook)
        .filter(ub.ArchivedBook.user_id == int(current_user.id))
        .filter(ub.ArchivedBook.is_archived == True)
        .all()
    )
    archived_book_ids = [archived_book.book_id for archived_book in archived_books]

    archived_filter = db.Books.id.in_(archived_book_ids)

    entries, random, pagination = calibre_db.fill_indexpage_with_archived_books(page, db.Books,
                                                                                0,
                                                                                archived_filter,
                                                                                order,
                                                                                True,
                                                                                False, 0)

    name = _(u'Archived Books') + ' (' + str(len(archived_book_ids)) + ')'
    pagename = "archived"
    return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                 title=name, page=pagename, order=sort_param[1])

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


