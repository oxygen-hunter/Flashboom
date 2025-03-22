def create_book_on_upload(modif_date, meta):
    title = meta.title
    authr = meta.author
    sort_authors, input_authors, db_author, renamed_authors = prepare_authors_on_upload(title, authr)

    title_dir = helper.get_valid_filename(title, chars=96)
    author_dir = helper.get_valid_filename(db_author.name, chars=96)

    # combine path and normalize path from windows systems
    path = os.path.join(author_dir, title_dir).replace('\\', '/')

    # Calibre adds books with utc as timezone
    db_book = db.Books(title, "", sort_authors, datetime.utcnow(), datetime(101, 1, 1),
                       '1', datetime.utcnow(), path, meta.cover, db_author, [], "")

    modif_date |= modify_database_object(input_authors, db_book.authors, db.Authors, calibre_db.session,
                                         'author')

    # Add series_index to book
    modif_date |= edit_book_series_index(meta.series_id, db_book)

    # add languages
    invalid=[]
    modif_date |= edit_book_languages(meta.languages, db_book, upload=True, invalid=invalid)
    if invalid:
        for l in invalid:
            flash(_(u"'%(langname)s' is not a valid language", langname=l), category="warning")

    # handle tags
    modif_date |= edit_book_tags(meta.tags, db_book)

    # handle publisher
    modif_date |= edit_book_publisher(meta.publisher, db_book)

    # handle series
    modif_date |= edit_book_series(meta.series, db_book)

    # Add file to book
    file_size = os.path.getsize(meta.file_path)
    db_data = db.Data(db_book, meta.extension.upper()[1:], file_size, title_dir)
    db_book.data.append(db_data)
    calibre_db.session.add(db_book)

    # flush content, get db_book.id available
    calibre_db.session.flush()
    return db_book, input_authors, title_dir, renamed_authors

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


