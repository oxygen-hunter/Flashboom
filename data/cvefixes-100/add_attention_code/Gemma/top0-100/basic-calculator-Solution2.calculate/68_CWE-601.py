def make_homeserver(self, reactor, clock):
    hs = self.setup_test_homeserver("server", http_client=None)
    self.store = hs.get_datastore()
    return hs

def calculate(self, s):
    operands, operators = [], []
    operand = ""
    for i in reversed(xrange(len(s))):
        if s[i].isdigit():
            operand += s[i]
            if i == 0 or not s[i-1].isdigit():
                operands.append(int(operand[::-1]))
                operand = ""
        elif s[i] == ')' or s[i] == '+' or s[i] == '-':
            operators.append(s[i])
        elif s[i] == '(':
            while operators[-1] != ')':
                self.compute(operands, operators)
            operators.pop()

    while operators:
        self.compute(operands, operators)

    return operands[-1]



