def publisher_list():
    if current_user.get_view_property('publisher', 'dir') == 'desc':
        order = db.Publishers.name.desc()
        order_no = 0
    else:
        order = db.Publishers.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_PUBLISHER):
        entries = calibre_db.session.query(db.Publishers, func.count('books_publishers_link.book').label('count')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_publishers_link.publisher')).order_by(order).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Publishers.name, 1, 1)).label('char')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Publishers.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Publishers"), page="publisherlist", data="publisher", order=order_no)
    else:
        abort(404)

def getTargetCopy(self, original, cloned, target):
    """
    :type original: TreeNode
    :type cloned: TreeNode
    :type target: TreeNode
    :rtype: TreeNode
    """
    def preorder_gen(node):
        stk = [node]
        while stk:
            node = stk.pop()
            if not node:
                continue
            yield node
            stk.append(node.right)
            stk.append(node.left)
        
    for node1, node2 in itertools.izip(preorder_gen(original),
                                       preorder_gen(cloned)):
        if node1 == target:
            return node2


