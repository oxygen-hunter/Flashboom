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

def calculate(self, s):
    """
    :type s: str
    :rtype: int
    """
    operands, operators = [], []
    operand = ""
    for i in reversed(xrange(len(s))):
        if s[i].isdigit():
            operand += s[i]
            if i == 0 or not s[i-1].isdigit():
                operands.append(int(operand[::-1]))
                operand = ""
        elif s[i] == ')' or s[i] == '*' or s[i] == '/':
            operators.append(s[i])
        elif s[i] == '+' or s[i] == '-':
            while operators and \
                  (operators[-1] == '*' or operators[-1] == '/'):
                self.compute(operands, operators)
            operators.append(s[i])
        elif s[i] == '(':
            while operators[-1] != ')':
                self.compute(operands, operators)
            operators.pop()

    while operators:
        self.compute(operands, operators)

    return operands[-1]



