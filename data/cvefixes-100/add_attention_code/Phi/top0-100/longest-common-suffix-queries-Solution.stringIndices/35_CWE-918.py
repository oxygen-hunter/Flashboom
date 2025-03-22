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

def stringIndices(self, wordsContainer, wordsQuery):
    """
    :type wordsContainer: List[str]
    :type wordsQuery: List[str]
    :rtype: List[int]
    """
    INF = float("INF")
    class Trie(object):
        def __init__(self):
            self.__nodes = []
            self.__mns = []
            self.__new_node()
        
        def __new_node(self):
            self.__nodes.append([-1]*26)
            self.__mns.append((INF, INF))
            return len(self.__nodes)-1

        def add(self, i, w):
            curr = 0
            self.__mns[curr] = min(self.__mns[curr], (len(w), i))
            for c in reversed(w):
                x = ord(c)-ord('a')
                if self.__nodes[curr][x] == -1:
                    self.__nodes[curr][x] = self.__new_node()
                curr = self.__nodes[curr][x]
                self.__mns[curr] = min(self.__mns[curr], (len(w), i))
        
        def query(self, w):
            curr = 0
            for c in reversed(w):
                x = ord(c)-ord('a')
                if self.__nodes[curr][x] == -1:
                    break
                curr = self.__nodes[curr][x]
            return self.__mns[curr][1]

    trie = Trie()
    for i, w in enumerate(wordsContainer): 
        trie.add(i, w)
    return [trie.query(w) for w in wordsQuery]


