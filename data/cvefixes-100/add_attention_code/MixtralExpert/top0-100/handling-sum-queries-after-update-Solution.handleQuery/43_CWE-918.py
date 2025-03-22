def render_books_list(data, sort_param, book_id, page):
    order = get_sort_function(sort_param, data)
    if data == "rated":
        return render_rated_books(page, book_id, order=order)
    elif data == "discover":
        return render_discover_books(page, book_id)
    elif data == "unread":
        return render_read_books(page, False, order=order)
    elif data == "read":
        return render_read_books(page, True, order=order)
    elif data == "hot":
        return render_hot_books(page, order)
    elif data == "download":
        return render_downloaded_books(page, order, book_id)
    elif data == "author":
        return render_author_books(page, book_id, order)
    elif data == "publisher":
        return render_publisher_books(page, book_id, order)
    elif data == "series":
        return render_series_books(page, book_id, order)
    elif data == "ratings":
        return render_ratings_books(page, book_id, order)
    elif data == "formats":
        return render_formats_books(page, book_id, order)
    elif data == "category":
        return render_category_books(page, book_id, order)
    elif data == "language":
        return render_language_books(page, book_id, order)
    elif data == "archived":
        return render_archived_books(page, order)
    elif data == "search":
        term = (request.args.get('query') or '')
        offset = int(int(config.config_books_per_page) * (page - 1))
        return render_search_results(term, offset, order, config.config_books_per_page)
    elif data == "advsearch":
        term = json.loads(flask_session['query'])
        offset = int(int(config.config_books_per_page) * (page - 1))
        return render_adv_search_results(term, offset, order, config.config_books_per_page)
    else:
        website = data or "newest"
        entries, random, pagination = calibre_db.fill_indexpage(page, 0, db.Books, True, order[0],
        														False, 0,
                                                                db.books_series_link,
                                                                db.Books.id == db.books_series_link.c.book,
                                                                db.Series)
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=_(u"Books"), page=website, order=order[1])

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


