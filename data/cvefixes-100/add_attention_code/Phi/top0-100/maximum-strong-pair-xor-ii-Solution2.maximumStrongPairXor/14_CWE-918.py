def author_list():
    if current_user.check_visibility(constants.SIDEBAR_AUTHOR):
        if current_user.get_view_property('author', 'dir') == 'desc':
            order = db.Authors.sort.desc()
            order_no = 0
        else:
            order = db.Authors.sort.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Authors, func.count('books_authors_link.book').label('count')) \
            .join(db.books_authors_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_authors_link.author')).order_by(order).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Authors.sort, 1, 1)).label('char')) \
            .join(db.books_authors_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Authors.sort, 1, 1))).all()
        # If not creating a copy, readonly databases can not display authornames with "|" in it as changing the name
        # starts a change session
        autor_copy = copy.deepcopy(entries)
        for entry in autor_copy:
            entry.Authors.name = entry.Authors.name.replace('|', ',')
        return render_title_template('list.html', entries=autor_copy, folder='web.books_list', charlist=charlist,
                                     title=u"Authors", page="authorlist", data='author', order=order_no)
    else:
        abort(404)

def maximumStrongPairXor(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    class Trie(object):
        def __init__(self, bit_length):
            self.__nodes = []
            self.__mins = []
            self.__maxs = []
            self.__new_node()
            self.__bit_length = bit_length
        
        def __new_node(self):
            self.__nodes.append([-1]*2)
            self.__mins.append(float("inf"))
            self.__maxs.append(float("-inf"))
            return len(self.__nodes)-1

        def insert(self, num):
            curr = 0
            for i in reversed(xrange(self.__bit_length)):
                x = num>>i
                if self.__nodes[curr][x&1] == -1:
                    self.__nodes[curr][x&1] = self.__new_node()
                curr = self.__nodes[curr][x&1]
                self.__mins[curr] = min(self.__mins[curr], num)
                self.__maxs[curr] = max(self.__maxs[curr], num)
                    
        def query(self, num):
            result = curr = 0
            for i in reversed(xrange(self.__bit_length)):
                result <<= 1
                x = num>>i
                y = (result|1)^x
                assert(x != y) 
                if (self.__nodes[curr][y&1] != -1 and
                    ((x > y and num <= 2*self.__maxs[self.__nodes[curr][y&1]]) or
                     (x < y and self.__mins[self.__nodes[curr][y&1]] <= 2*num))):
                    result |= 1
                    curr = self.__nodes[curr][y&1]
                else:
                    curr = self.__nodes[curr][1^(y&1)]
            return result

    trie = Trie(max(nums).bit_length())
    result = 0
    for num in nums:
        trie.insert(num)
        result = max(result, trie.query(num))
    return result



