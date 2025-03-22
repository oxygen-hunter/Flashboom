def render_prepare_search_form(cc):
    # prepare data for search-form
    tags = calibre_db.session.query(db.Tags)\
        .join(db.books_tags_link)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(text('books_tags_link.tag'))\
        .order_by(db.Tags.name).all()
    series = calibre_db.session.query(db.Series)\
        .join(db.books_series_link)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(text('books_series_link.series'))\
        .order_by(db.Series.name)\
        .filter(calibre_db.common_filters()).all()
    shelves = ub.session.query(ub.Shelf)\
        .filter(or_(ub.Shelf.is_public == 1, ub.Shelf.user_id == int(current_user.id)))\
        .order_by(ub.Shelf.name).all()
    extensions = calibre_db.session.query(db.Data)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(db.Data.format)\
        .order_by(db.Data.format).all()
    if current_user.filter_language() == u"all":
        languages = calibre_db.speaking_language()
    else:
        languages = None
    return render_title_template('search_form.html', tags=tags, languages=languages, extensions=extensions,
                                 series=series,shelves=shelves, title=_(u"Advanced Search"), cc=cc, page="advsearch")

def sumOddLengthSubarrays(self, arr):
    """
    :type arr: List[int]
    :rtype: int
    """
    def ceil_divide(a, b):
        return (a+(b-1))//b
 
    # begin\pos |0   i       (n-1)
    # ----------------------------
    # 0          --101....      ↑
    # 1           -010....    i-0+1
    # i            101....      ↓
    #              ← (n-1-i+1) →
    #
    # for each number x with its position i, we want to know how many odd length subarrays is with x,
    # as the graph depicted above,
    # (begin, pos) pair represents a subarray arr[begin:pos+1] containing x, marked 1 if odd length else 0,
    # so the total number of 0 and 1 are exactly the total number of subarrays with x, which is (i-0+1)*((len(arr)-1)-i+1),
    # because the number of 1 is always equal to or one more than the number of 0, (always begins with 1010... and alternatively flips)
    # so there are ceil((i-0+1)*((len(arr)-1)-i+1)/2) odd length subarrays with x
    # 
    return sum(x * ceil_divide((i-0+1)*((len(arr)-1)-i+1), 2) for i, x in enumerate(arr))


