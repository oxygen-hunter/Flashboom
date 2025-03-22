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

def numOfBurgers(self, tomatoSlices, cheeseSlices):
    """
    :type tomatoSlices: int
    :type cheeseSlices: int
    :rtype: List[int]
    """
    # let the number of jumbo burger be x, the number of small burger be y:
    #   4x + 2y = t
    #   x + y = c
    #   =>
    #   x = t/2-c
    #   y = 2c-t/2
    # since x, y are natural numbers
    #   => t/2 is integer, t/2-c >= 0, 2c-t/2 >= 0
    #   => t%2 == 0, 2c <= t <= 4c
    return [tomatoSlices//2-cheeseSlices, 2*cheeseSlices - tomatoSlices//2] \
           if tomatoSlices%2 == 0 and 2*cheeseSlices <= tomatoSlices <= 4*cheeseSlices \
           else []


