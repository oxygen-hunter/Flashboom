def render_hot_books(page, order):
    if current_user.check_visibility(constants.SIDEBAR_HOT):
        if order[1] not in ['hotasc', 'hotdesc']:
        # Unary expression comparsion only working (for this expression) in sqlalchemy 1.4+
        #if not (order[0][0].compare(func.count(ub.Downloads.book_id).desc()) or
        #        order[0][0].compare(func.count(ub.Downloads.book_id).asc())):
            order = [func.count(ub.Downloads.book_id).desc()], 'hotdesc'
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()
        off = int(int(config.config_books_per_page) * (page - 1))
        all_books = ub.session.query(ub.Downloads, func.count(ub.Downloads.book_id))\
            .order_by(*order[0]).group_by(ub.Downloads.book_id)
        hot_books = all_books.offset(off).limit(config.config_books_per_page)
        entries = list()
        for book in hot_books:
            downloadBook = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()).filter(
                db.Books.id == book.Downloads.book_id).first()
            if downloadBook:
                entries.append(downloadBook)
            else:
                ub.delete_download(book.Downloads.book_id)
        numBooks = entries.__len__()
        pagination = Pagination(page, config.config_books_per_page, numBooks)
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=_(u"Hot Books (Most Downloaded)"), page="hot", order=order[1])
    else:
        abort(404)

def canMerge(self, trees):
    """
    :type trees: List[TreeNode]
    :rtype: TreeNode
    """
    def find_leaves_and_roots(trees, leaf_vals_set, val_to_root):
        for root in trees:
            val_to_root[root.val] = root
            q = [root]
            while q:
                new_q = []
                for node in q:
                    if node.left is None and node.right is None:
                        if node is not root:
                            leaf_vals_set.add(node.val)
                        continue
                    if node.left:
                        new_q.append(node.left)
                    if node.right:
                        new_q.append(node.right)
                q = new_q

    def find_root(trees, left_vals_set, val_to_root):
        root = None
        for node in trees:
            if node.val in leaf_vals_set:
                continue
            if root:  # multiple roots
                return None
            root = node
        return root

    def merge_bsts(root, left_vals_set, val_to_root):
        if not root:
            return None
        del val_to_root[root.val]
        q = [(root, float("-inf"), float("inf"))]
        while q:
            new_q = []
            for node, left, right in q:
                if not (left < node.val < right):
                    return None
                if node.left:
                    if node.left.val in leaf_vals_set and node.left.val in val_to_root:
                        node.left = val_to_root[node.left.val]
                        del val_to_root[node.left.val]
                    new_q.append((node.left, left, node.val))
                if node.right:
                    if node.right.val in leaf_vals_set and node.right.val in val_to_root:
                        node.right = val_to_root[node.right.val]
                        del val_to_root[node.right.val]
                    new_q.append((node.right, node.val, right))
            q = new_q
        return root if not val_to_root else None

    leaf_vals_set, val_to_root = set(), {}
    find_leaves_and_roots(trees, leaf_vals_set, val_to_root)    
    root = find_root(trees, leaf_vals_set, val_to_root)
    return merge_bsts(root, leaf_vals_set, val_to_root)


