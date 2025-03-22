def read_book(book_id, book_format):
    book = calibre_db.get_filtered_book(book_id)
    book.ordered_authors = calibre_db.order_authors([book], False)

    if not book:
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"), category="error")
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        return redirect(url_for("web.index"))

    # check if book has a bookmark
    bookmark = None
    if current_user.is_authenticated:
        bookmark = ub.session.query(ub.Bookmark).filter(and_(ub.Bookmark.user_id == int(current_user.id),
                                                             ub.Bookmark.book_id == book_id,
                                                             ub.Bookmark.format == book_format.upper())).first()
    if book_format.lower() == "epub":
        log.debug(u"Start epub reader for %d", book_id)
        return render_title_template('read.html', bookid=book_id, title=book.title, bookmark=bookmark)
    elif book_format.lower() == "pdf":
        log.debug(u"Start pdf reader for %d", book_id)
        return render_title_template('readpdf.html', pdffile=book_id, title=book.title)
    elif book_format.lower() == "txt":
        log.debug(u"Start txt reader for %d", book_id)
        return render_title_template('readtxt.html', txtfile=book_id, title=book.title)
    elif book_format.lower() == "djvu":
        log.debug(u"Start djvu reader for %d", book_id)
        return render_title_template('readdjvu.html', djvufile=book_id, title=book.title)
    else:
        for fileExt in constants.EXTENSIONS_AUDIO:
            if book_format.lower() == fileExt:
                entries = calibre_db.get_filtered_book(book_id)
                log.debug(u"Start mp3 listening for %d", book_id)
                return render_title_template('listenmp3.html', mp3file=book_id, audioformat=book_format.lower(),
                                             entry=entries, bookmark=bookmark)
        for fileExt in ["cbr", "cbt", "cbz"]:
            if book_format.lower() == fileExt:
                all_name = str(book_id)
                title = book.title
                if len(book.series):
                    title = title + " - " + book.series[0].name
                    if book.series_index:
                        title = title + " #" + '{0:.2f}'.format(book.series_index).rstrip('0').rstrip('.')
                log.debug(u"Start comic reader for %d", book_id)
                return render_title_template('readcbr.html', comicfile=all_name, title=title,
                                             extension=fileExt)
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"), category="error")
        return redirect(url_for("web.index"))

def handleQuery(self, nums1, nums2, queries):
    """
    :type nums1: List[int]
    :type nums2: List[int]
    :type queries: List[List[int]]
    :rtype: List[int]
    """
    class SegmentTree(object):  # 0-based index
        def __init__(self, N,
                    build_fn=lambda _: 0,
                    query_fn=lambda x, y: y if x is None else max(x, y),
                    update_fn=lambda x, y: y if x is None else x+y):
            self.base = N
            self.H = (N-1).bit_length()
            self.query_fn = query_fn
            self.update_fn = update_fn
            self.tree = [None]*(2*N)
            self.lazy = [None]*N
            for i in xrange(self.base, self.base+N):
                self.tree[i] = build_fn(i-self.base)
            for i in reversed(xrange(1, self.base)):
                self.tree[i] = query_fn(self.tree[2*i], self.tree[2*i+1])

        def __apply(self, x, val):
            self.tree[x] = self.update_fn(self.tree[x], val)
            if x < self.base:
                self.lazy[x] = self.update_fn(self.lazy[x], val)

        def update(self, L, R, h):  # Time: O(logN), Space: O(N)
            def pull(x):
                while x > 1:
                    x >>= 1
                    self.tree[x] = self.query_fn(self.tree[x<<1], self.tree[(x<<1)+1])
                    if self.lazy[x] is not None:
                        self.tree[x] = self.update_fn(self.tree[x], self.lazy[x])

            if L > R:
                return
            L += self.base
            R += self.base
            L0, R0 = L, R
            while L <= R:
                if L & 1:  # is right child
                    self.__apply(L, h)
                    L += 1
                if R & 1 == 0:  # is left child
                    self.__apply(R, h)
                    R -= 1
                L >>= 1
                R >>= 1
            pull(L0)
            pull(R0)

        def query(self, L, R):  # Time: O(logN), Space: O(N)
            def push(x):
                n = self.H
                while n:
                    y = x >> n
                    if self.lazy[y] is not None:
                        self.__apply(y<<1, self.lazy[y])
                        self.__apply((y<<1)+1, self.lazy[y])
                        self.lazy[y] = None
                    n -= 1

            result = None
            if L > R:
                return result

            L += self.base
            R += self.base
            push(L)
            push(R)
            while L <= R:
                if L & 1:  # is right child
                    result = self.query_fn(result, self.tree[L])
                    L += 1
                if R & 1 == 0:  # is left child
                    result = self.query_fn(result, self.tree[R])
                    R -= 1
                L >>= 1
                R >>= 1
            return result

    st = SegmentTree(len(nums1),
                     build_fn=lambda i: (nums1[i], nums1[i]^1),
                     query_fn=lambda x, y: y if x is None else (x[0]+y[0], x[1]+y[1]),
                     update_fn=lambda x, y: y if x is None else (x[1], x[0]) if y == (1, 0) else x)
    result = []
    total = sum(nums2)
    for t, a, b in queries:
        if t == 1:
            st.update(a, b, (1, 0))
        elif t == 2:
            total += st.query(0, len(nums1)-1)[0]*a
        elif t == 3:
            result.append(total)
    return result


