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

def kthLargestPerfectSubtree(self, root, k):
    """
    :type root: Optional[TreeNode]
    :type k: int
    :rtype: int
    """
    def nth_element(nums, left, n, right, compare=lambda a, b: a < b):
        def tri_partition(nums, left, right, target):
            i = left
            while i <= right:
                if compare(nums[i], target):
                    nums[i], nums[left] = nums[left], nums[i]
                    left += 1
                    i += 1
                elif compare(target, nums[i]):
                    nums[i], nums[right] = nums[right], nums[i]
                    right -= 1
                else:
                    i += 1
            return left, right

        while left <= right:
            pivot_idx = random.randint(left, right)
            pivot_left, pivot_right = tri_partition(nums, left, right, nums[pivot_idx])
            if pivot_left <= n <= pivot_right:
                return
            elif pivot_left > n:
                right = pivot_left-1
            else:  # pivot_right < n.
                left = pivot_right+1

    def dfs(curr):
        if not curr:
            result.append(0)
            return
        dfs(curr.left)
        left = result[-1]
        dfs(curr.right)
        right = result[-1]
        result.append(left+right+1 if left == right != -1 else -1)

    result = []
    dfs(root)
    nth_element(result, 0, k-1, len(result)-1, lambda a, b: a > b)
    return result[k-1] if k-1 < len(result) and result[k-1] > 0 else -1


