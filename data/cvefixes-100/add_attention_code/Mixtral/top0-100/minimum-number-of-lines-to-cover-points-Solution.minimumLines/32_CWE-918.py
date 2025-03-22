def profile():
    languages = calibre_db.speaking_language()
    translations = babel.list_translations() + [LC('en')]
    kobo_support = feature_support['kobo'] and config.config_kobo_sync
    if feature_support['oauth'] and config.config_login_type == 2:
        oauth_status = get_oauth_status()
        local_oauth_check = oauth_check
    else:
        oauth_status = None
        local_oauth_check = {}

    if request.method == "POST":
        change_profile(kobo_support, local_oauth_check, oauth_status, translations, languages)
    return render_title_template("user_edit.html",
                                 translations=translations,
                                 profile=1,
                                 languages=languages,
                                 content=current_user,
                                 kobo_support=kobo_support,
                                 title=_(u"%(name)s's profile", name=current_user.name),
                                 page="me",
                                 registered_oauth=local_oauth_check,
                                 oauth_status=oauth_status)

def minimumLines(self, points):
    """
    :type points: List[List[int]]
    :rtype: int
    """
    def gcd(a, b):  # Time: O(log(a + b))
        while b:
            a, b = b, a % b
        return a

    def popcount(x):
        result = 0
        while x:
            x &= (x-1)
            result += 1
        return result

    def ceil_divide(a, b):
        return (a+b-1)//b
    
    lookup = collections.defaultdict(set)               
    for i, (x1, y1) in enumerate(points):
        for j in xrange(i+1, len(points)):
            x2, y2 = points[j]
            # (x-x1)/(x2-x1) = (y-y1)/(y2-y1)
            # => (y2-y1)x - (x2-x1)y = x1(y2-y1) - y1(x2-x1)
            a, b, c = (y2-y1), -(x2-x1), x1*(y2-y1)-y1*(x2-x1) 
            g = gcd(gcd(a, b), c)
            a, b, c = a//g, b//g, c//g
            lookup[(a, b, c)].add((x1, y1))
            lookup[(a, b, c)].add((x2, y2))
    lines = [l for l, p in lookup.iteritems() if len(p) > 2]  # filter to improve complexity
    assert(len(lines) <= (len(points))//2)  # 1 extra colinear point per 2 points
    result = float("inf")
    for mask in xrange(1<<len(lines)):
        covered = set()
        bit, i = 1, 0
        while bit <= mask:
            if mask&bit:
                covered.update(lookup[lines[i]])
            bit <<= 1                        
            i += 1
        result = min(result, popcount(mask) + ceil_divide(len(points)-len(covered), 2))
    return result


