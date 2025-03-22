def render_read_books(page, are_read, as_xml=False, order=None):
    sort_param = order[0] if order else []
    if not config.config_read_column:
        if are_read:
            db_filter = and_(ub.ReadBook.user_id == int(current_user.id),
                             ub.ReadBook.read_status == ub.ReadBook.STATUS_FINISHED)
        else:
            db_filter = coalesce(ub.ReadBook.read_status, 0) != ub.ReadBook.STATUS_FINISHED
        entries, random, pagination = calibre_db.fill_indexpage(page, 0,
                                                                db.Books,
                                                                db_filter,
                                                                sort_param,
                                                                False, 0,
                                                                db.books_series_link,
                                                                db.Books.id == db.books_series_link.c.book,
                                                                db.Series,
                                                                ub.ReadBook, db.Books.id == ub.ReadBook.book_id)
    else:
        try:
            if are_read:
                db_filter = db.cc_classes[config.config_read_column].value == True
            else:
                db_filter = coalesce(db.cc_classes[config.config_read_column].value, False) != True
            entries, random, pagination = calibre_db.fill_indexpage(page, 0,
                                                                    db.Books,
                                                                    db_filter,
                                                                    sort_param,
                                                                    False, 0,
                                                                    db.books_series_link,
                                                                    db.Books.id == db.books_series_link.c.book,
                                                                    db.Series,
                                                                    db.cc_classes[config.config_read_column])
        except (KeyError, AttributeError):
            log.error("Custom Column No.%d is not existing in calibre database", config.config_read_column)
            if not as_xml:
                flash(_("Custom Column No.%(column)d is not existing in calibre database",
                        column=config.config_read_column),
                      category="error")
                return redirect(url_for("web.index"))
            return [] # ToDo: Handle error Case for opds

    if as_xml:
        return entries, pagination
    else:
        if are_read:
            name = _(u'Read Books') + ' (' + str(pagination.total_count) + ')'
            pagename = "read"
        else:
            name = _(u'Unread Books') + ' (' + str(pagination.total_count) + ')'
            pagename = "unread"
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=name, page=pagename, order=order[1])

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



