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

def carArrived(self, carId, roadId, direction, turnGreen, crossCar):
    """
    :type roadId: int --> // ID of the car
    :type carId: int --> // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
    :type direction: int --> // Direction of the car
    :type turnGreen: method --> // Use turnGreen() to turn light to green on current road
    :type crossCar: method --> // Use crossCar() to make car cross the intersection
    :rtype: void
    """
    with self.__l:
        if self.__light != roadId:
            self.__light = roadId
            turnGreen()
        crossCar()


