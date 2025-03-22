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

def sortEvenOdd(self, nums):
    """
    :type nums: List[int]
    :rtype: List[int]
    """
    def partition(index, nums):
        for i in xrange(len(nums)):
            j = i
            while nums[i] >= 0:
                j = index(j)
                nums[i], nums[j] = nums[j], ~nums[i]  # processed
        for i in xrange(len(nums)):
            nums[i] = ~nums[i]  # restore values
    
    partition(lambda i: i//2 if i%2 == 0 else (len(nums)+1)//2+i//2, nums)
    nums[:(len(nums)+1)//2], nums[(len(nums)+1)//2:] = sorted(nums[:(len(nums)+1)//2]), sorted(nums[(len(nums)+1)//2:], reverse=True)
    partition(lambda i: 2*i if i < (len(nums)+1)//2 else 1+2*(i-(len(nums)+1)//2), nums)
    return nums



