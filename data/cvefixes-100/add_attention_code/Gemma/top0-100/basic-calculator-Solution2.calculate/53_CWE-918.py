def render_search_results(term, offset=None, order=None, limit=None):
    join = db.books_series_link, db.Books.id == db.books_series_link.c.book, db.Series
    entries, result_count, pagination = calibre_db.get_search_results(term,
                                                                      offset,
                                                                      order,
                                                                      limit,
                                                                      False,
                                                                      config.config_read_column,
                                                                      *join)
    return render_title_template('search.html',
                                 searchterm=term,
                                 pagination=pagination,
                                 query=term,
                                 adv_searchterm=term,
                                 entries=entries,
                                 result_count=result_count,
                                 title=_(u"Search"),
                                 page="search",
                                 order=order[1])

def calculate(self, s):
    operands, operators = [], []
    operand = ""
    for i in reversed(xrange(len(s))):
        if s[i].isdigit():
            operand += s[i]
            if i == 0 or not s[i-1].isdigit():
                operands.append(int(operand[::-1]))
                operand = ""
        elif s[i] == ')' or s[i] == '+' or s[i] == '-':
            operators.append(s[i])
        elif s[i] == '(':
            while operators[-1] != ')':
                self.compute(operands, operators)
            operators.pop()

    while operators:
        self.compute(operands, operators)

    return operands[-1]



