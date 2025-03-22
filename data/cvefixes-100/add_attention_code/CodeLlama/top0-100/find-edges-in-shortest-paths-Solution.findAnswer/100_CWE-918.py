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

def findAnswer(self, n, edges):
    """
    :type n: int
    :type edges: List[List[int]]
    :rtype: List[bool]
    """
    INF = float("inf")
    def dijkstra(start):
        best = [INF]*len(adj)
        best[start] = 0
        min_heap = [(0, start)]
        while min_heap:
            curr, u = heapq.heappop(min_heap)
            if curr > best[u]:
                continue
            for v, w in adj[u]:     
                if best[v] <= curr+w:
                    continue
                best[v] = curr+w
                heapq.heappush(min_heap, (best[v], v))
        return best

    adj = [[] for _ in xrange(n)]
    for u, v, w in edges:
        adj[u].append((v, w))
        adj[v].append((u, w))
    dist1 = dijkstra(0)
    dist2 = dijkstra(n-1)
    return [(dist1[u] != INF != dist2[v] and dist1[u]+w+dist2[v] == dist1[n-1]) or
            (dist2[u] != INF != dist1[v] and dist2[u]+w+dist1[v] == dist2[0])
            for i, (u, v, w) in enumerate(edges)]


