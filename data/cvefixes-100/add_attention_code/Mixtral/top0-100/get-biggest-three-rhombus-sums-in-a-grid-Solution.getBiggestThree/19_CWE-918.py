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

def getBiggestThree(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: List[int]
    """	
    K = 3
    left = [[grid[i][j] for j in xrange(len(grid[i]))] for i in xrange(len(grid))]
    right = [[grid[i][j] for j in xrange(len(grid[i]))] for i in xrange(len(grid))]
    for i in xrange(1, len(grid)):
        for j in xrange(len(grid[0])-1):
            left[i][j] += left[i-1][j+1]
    for i in xrange(1, len(grid)):
        for j in xrange(1, len(grid[0])):
            right[i][j] += right[i-1][j-1]
    min_heap = []
    lookup = set()
    for k in xrange((min(len(grid), len(grid[0]))+1)//2):
        for i in xrange(k, len(grid)-k):
            for j in xrange(k, len(grid[0])-k):
                total = (((left[i][j-k]-left[i-k][j])+(right[i][j+k]-right[i-k][j])+grid[i-k][j]) +  
                         ((left[i+k][j]-left[i][j+k])+(right[i+k][j]-right[i][j-k])-grid[i+k][j])) if k else grid[i][j]
                if total in lookup:
                    continue
                lookup.add(total)
                heapq.heappush(min_heap, total)
                if len(min_heap) == K+1:                        
                    lookup.remove(heapq.heappop(min_heap))
    min_heap.sort(reverse=True)
    return min_heap


