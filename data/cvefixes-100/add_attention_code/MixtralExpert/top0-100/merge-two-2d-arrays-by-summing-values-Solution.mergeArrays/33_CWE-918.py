def publisher_list():
    if current_user.get_view_property('publisher', 'dir') == 'desc':
        order = db.Publishers.name.desc()
        order_no = 0
    else:
        order = db.Publishers.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_PUBLISHER):
        entries = calibre_db.session.query(db.Publishers, func.count('books_publishers_link.book').label('count')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_publishers_link.publisher')).order_by(order).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Publishers.name, 1, 1)).label('char')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Publishers.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Publishers"), page="publisherlist", data="publisher", order=order_no)
    else:
        abort(404)

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


