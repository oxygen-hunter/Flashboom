def download_list():
    if current_user.get_view_property('download', 'dir') == 'desc':
        order = ub.User.name.desc()
        order_no = 0
    else:
        order = ub.User.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD) and current_user.role_admin():
        entries = ub.session.query(ub.User, func.count(ub.Downloads.book_id).label('count'))\
            .join(ub.Downloads).group_by(ub.Downloads.user_id).order_by(order).all()
        charlist = ub.session.query(func.upper(func.substr(ub.User.name, 1, 1)).label('char')) \
            .filter(ub.User.role.op('&')(constants.ROLE_ANONYMOUS) != constants.ROLE_ANONYMOUS) \
            .group_by(func.upper(func.substr(ub.User.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Downloads"), page="downloadlist", data="download", order=order_no)
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


