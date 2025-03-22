def convert_bookformat(book_id):
    # check to see if we have form fields to work with -  if not send user back
    book_format_from = request.form.get('book_format_from', None)
    book_format_to = request.form.get('book_format_to', None)

    if (book_format_from is None) or (book_format_to is None):
        flash(_(u"Source or destination format for conversion missing"), category="error")
        return redirect(url_for('editbook.edit_book', book_id=book_id))

    log.info('converting: book id: %s from: %s to: %s', book_id, book_format_from, book_format_to)
    rtn = helper.convert_book_format(book_id, config.config_calibre_dir, book_format_from.upper(),
                                     book_format_to.upper(), current_user.name)

    if rtn is None:
        flash(_(u"Book successfully queued for converting to %(book_format)s",
                    book_format=book_format_to),
                    category="success")
    else:
        flash(_(u"There was an error converting this book: %(res)s", res=rtn), category="error")
    return redirect(url_for('editbook.edit_book', book_id=book_id))

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



