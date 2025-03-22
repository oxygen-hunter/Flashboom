def ratings_list():
    if current_user.check_visibility(constants.SIDEBAR_RATING):
        if current_user.get_view_property('ratings', 'dir') == 'desc':
            order = db.Ratings.rating.desc()
            order_no = 0
        else:
            order = db.Ratings.rating.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Ratings, func.count('books_ratings_link.book').label('count'),
                                   (db.Ratings.rating / 2).label('name')) \
            .join(db.books_ratings_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_ratings_link.rating')).order_by(order).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=list(),
                                     title=_(u"Ratings list"), page="ratingslist", data="ratings", order=order_no)
    else:
        abort(404)

def __iterative_backtracking(self):
    def conquer():
        if len(curr) == self.__combinationLength:
            return curr

    def prev_divide(c):
        curr.append(c)
    
    def divide(i):
        if len(curr) != self.__combinationLength:
            for j in reversed(xrange(i, len(self.__characters)-(self.__combinationLength-len(curr)-1))):
                stk.append(functools.partial(post_divide))
                stk.append(functools.partial(divide, j+1))
                stk.append(functools.partial(prev_divide, self.__characters[j]))
        stk.append(functools.partial(conquer))

    def post_divide():
        curr.pop()
        
    curr = []
    stk = [functools.partial(divide, 0)]
    while stk:
        result = stk.pop()()
        if result is not None:
            yield result



