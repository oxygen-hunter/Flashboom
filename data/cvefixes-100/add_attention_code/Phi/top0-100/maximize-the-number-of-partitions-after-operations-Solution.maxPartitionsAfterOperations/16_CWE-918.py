def category_list():
    if current_user.check_visibility(constants.SIDEBAR_CATEGORY):
        if current_user.get_view_property('category', 'dir') == 'desc':
            order = db.Tags.name.desc()
            order_no = 0
        else:
            order = db.Tags.name.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Tags, func.count('books_tags_link.book').label('count')) \
            .join(db.books_tags_link).join(db.Books).order_by(order).filter(calibre_db.common_filters()) \
            .group_by(text('books_tags_link.tag')).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Tags.name, 1, 1)).label('char')) \
            .join(db.books_tags_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Tags.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Categories"), page="catlist", data="category", order=order_no)
    else:
        abort(404)

def maxPartitionsAfterOperations(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: int
    """
    def popcount(n):
        n = (n & 0x55555555) + ((n >> 1) & 0x55555555)
        n = (n & 0x33333333) + ((n >> 2) & 0x33333333)
        n = (n & 0x0F0F0F0F) + ((n >> 4) & 0x0F0F0F0F)
        n = (n & 0x00FF00FF) + ((n >> 8) & 0x00FF00FF)
        n = (n & 0x0000FFFF) + ((n >> 16) & 0x0000FFFF)
        return n

    left = [0]*(len(s)+1)
    left_mask = [0]*(len(s)+1)
    cnt = mask = 0
    for i in xrange(len(s)):
        mask |= 1<<(ord(s[i])-ord('a'))
        if popcount(mask) > k:
            cnt += 1
            mask = 1<<(ord(s[i])-ord('a'))
        left[i+1] = cnt
        left_mask[i+1] = mask
    right = [0]*(len(s)+1)
    right_mask = [0]*(len(s)+1)
    cnt = mask = 0
    for i in reversed(xrange(len(s))):
        mask |= 1<<(ord(s[i])-ord('a'))
        if popcount(mask) > k:
            cnt += 1
            mask = 1<<(ord(s[i])-ord('a'))
        right[i] = cnt
        right_mask[i] = mask

    result = 0
    for i in xrange(len(s)):
        curr = left[i]+right[i+1]
        mask = left_mask[i]|right_mask[i+1]
        if popcount(left_mask[i]) == popcount(right_mask[i+1]) == k and popcount(mask) != 26:
            curr += 3
        elif popcount(mask)+int(popcount(mask) != 26) > k:  # test case: s = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", k = 26
            curr += 2
        else:
            curr += 1
        result = max(result, curr)
    return result


