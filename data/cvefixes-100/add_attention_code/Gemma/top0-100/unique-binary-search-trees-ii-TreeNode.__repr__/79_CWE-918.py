def _check_login_status(self, request: Request) -> LoginButton:
    # Each time the page is refreshed or loaded, check if the user is logged in and adapt label
    session = getattr(request, "session", None) or getattr(
        request.request, "session", None
    )
    if session is None or "oauth_info" not in session:
        return LoginButton(value=self.value, interactive=True)
    else:
        username = session["oauth_info"]["userinfo"]["preferred_username"]
        logout_text = self.logout_value.format(username)
        return LoginButton(logout_text, interactive=True)

def __repr__(self):
    if self:
        serial = []
        queue = [self]

        while queue:
            cur = queue[0]

            if cur:
                serial.append(cur.val)
                queue.append(cur.left)
                queue.append(cur.right)
            else:
                serial.append("#")

            queue = queue[1:]

        while serial[-1] == "#":
            serial.pop()

        return repr(serial)

    else:
        return None



