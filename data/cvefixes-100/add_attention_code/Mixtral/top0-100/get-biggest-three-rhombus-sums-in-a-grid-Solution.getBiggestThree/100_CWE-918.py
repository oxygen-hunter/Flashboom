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

def getBiggestThree(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: List[int]
    """	
    K = 3
    left = [[grid[i][j] for j in xrange(len(grid[i]))] for i in xrange(len(grid))]
    right = [[grid[i][j] for j in xrange(len(grid[i]))] for i in xrange(len(grid))]
    for i in xrange(1, len(grid)):
        for j in xrange(len(grid[0])-1):
            left[i][j] += left[i-1][j+1]
    for i in xrange(1, len(grid)):
        for j in xrange(1, len(grid[0])):
            right[i][j] += right[i-1][j-1]
    min_heap = []
    lookup = set()
    for k in xrange((min(len(grid), len(grid[0]))+1)//2):
        for i in xrange(k, len(grid)-k):
            for j in xrange(k, len(grid[0])-k):
                total = (((left[i][j-k]-left[i-k][j])+(right[i][j+k]-right[i-k][j])+grid[i-k][j]) +  
                         ((left[i+k][j]-left[i][j+k])+(right[i+k][j]-right[i][j-k])-grid[i+k][j])) if k else grid[i][j]
                if total in lookup:
                    continue
                lookup.add(total)
                heapq.heappush(min_heap, total)
                if len(min_heap) == K+1:                        
                    lookup.remove(heapq.heappop(min_heap))
    min_heap.sort(reverse=True)
    return min_heap


