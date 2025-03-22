def _get_unauth_response(self, request, reason):
    """
    Get an error response (or raise a Problem) for a given request and reason message.

    :type request: Request.
    :param request: HttpRequest
    :type reason: Reason string.
    :param reason: str
    """
    if request.is_ajax():
        return HttpResponseForbidden(json.dumps({"error": force_text(reason)}))
    error_params = urlencode({"error": force_text(reason)})
    login_url = force_str(reverse("shuup_admin:login") + "?" + error_params)
    resp = redirect_to_login(next=request.path, login_url=login_url)
    if is_authenticated(request.user):
        # Instead of redirecting to the login page, let the user know what's wrong with
        # a helpful link.
        raise (
            Problem(_("Can't view this page. %(reason)s") % {"reason": reason}).with_link(
                url=resp.url, title=_("Log in with different credentials...")
            )
        )
    return resp

def findAllRecipes(self, recipes, ingredients, supplies):
    """
    :type recipes: List[str]
    :type ingredients: List[List[str]]
    :type supplies: List[str]
    :rtype: List[str]
    """
    indegree = collections.defaultdict(int)
    adj = collections.defaultdict(list)
    for r, ingredient in itertools.izip(recipes, ingredients): 
        indegree[r] = len(ingredient)
        for ing in ingredient:
            adj[ing].append(r)
    result = []
    recipes = set(recipes)
    q = supplies
    while q: 
        new_q = []
        for u in q:
            if u in recipes:
                result.append(u)
            for v in adj[u]:
                indegree[v] -= 1
                if not indegree[v]:
                    new_q.append(v)
        q = new_q
    return result 


