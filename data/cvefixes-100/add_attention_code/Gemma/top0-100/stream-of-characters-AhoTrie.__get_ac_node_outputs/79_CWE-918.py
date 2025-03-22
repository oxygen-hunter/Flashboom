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

def __get_ac_node_outputs(self, node):  # Time:  O(z), in this question, it could be improved to O(1)
                                        # if we only return a matched pattern without all matched ones
    result = []
    for i in node.indices:
        result.append(i)
        # return result
    output = node.output
    while output:
        for i in output.indices:
            result.append(i)
            # return result
        output = output.output
    return result



