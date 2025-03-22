def render_downloaded_books(page, order, user_id):
    if current_user.role_admin():
        user_id = int(user_id)
    else:
        user_id = current_user.id
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD):
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()

        entries, __, pagination = calibre_db.fill_indexpage(page,
                                                            0,
                                                            db.Books,
                                                            ub.Downloads.user_id == user_id,
                                                            order[0],
                                                            False, 0,
                                                            db.books_series_link,
                                                            db.Books.id == db.books_series_link.c.book,
                                                            db.Series,
                                                            ub.Downloads, db.Books.id == ub.Downloads.book_id)
        for book in entries:
            if not calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                             .filter(db.Books.id == book.id).first():
                ub.delete_download(book.id)
        user = ub.session.query(ub.User).filter(ub.User.id == user_id).first()
        return render_title_template('index.html',
                                     random=random,
                                     entries=entries,
                                     pagination=pagination,
                                     id=user_id,
                                     title=_(u"Downloaded books by %(user)s",user=user.name),
                                     page="download",
                                     order=order[1])
    else:
        abort(404)

def maxBalancedSubsequenceSum(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    NEG_INF = float("-inf")
    # Range Maximum Query
    class SegmentTree(object):
        def __init__(self, N,
                     build_fn=lambda _: None,
                     query_fn=lambda x, y: max(x, y),
                     update_fn=lambda x, y: max(x, y)):
            self.tree = [None]*(2*2**((N-1).bit_length()))
            self.base = len(self.tree)//2
            self.query_fn = query_fn
            self.update_fn = update_fn
            for i in xrange(self.base, self.base+N):
                self.tree[i] = build_fn(i-self.base)
            for i in reversed(xrange(1, self.base)):
                self.tree[i] = query_fn(self.tree[2*i], self.tree[2*i+1])

        def update(self, i, h):
            x = self.base+i
            self.tree[x] = self.update_fn(self.tree[x], h)
            while x > 1:
                x //= 2
                self.tree[x] = self.query_fn(self.tree[x*2], self.tree[x*2+1])

        def query(self, L, R):
            if L > R:
                return None
            L += self.base
            R += self.base
            left = right = None
            while L <= R:
                if L & 1:
                    left = self.query_fn(left, self.tree[L])
                    L += 1
                if R & 1 == 0:
                    right = self.query_fn(self.tree[R], right)
                    R -= 1
                L //= 2
                R //= 2
            return self.query_fn(left, right)

    val_to_idx = {x:i for i, x in enumerate(sorted({x-i for i, x in enumerate(nums)}))}
    st = SegmentTree(len(val_to_idx))
    for i, x in enumerate(nums):
        v = max(st.query(0, val_to_idx[x-i]), 0)+x
        st.update(val_to_idx[x-i], v)
    return st.query(0, len(val_to_idx)-1)


