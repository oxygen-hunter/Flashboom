def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def copyRandomList(self, head):
    dummy = Node(0)
    current, prev, copies = head, dummy, {}

    while current:
        copied = Node(current.val)
        copies[current] = copied
        prev.next = copied
        prev, current = prev.next, current.next

    current = head
    while current:
        if current.random:
            copies[current].random = copies[current.random]
        current = current.next

    return dummy.next



