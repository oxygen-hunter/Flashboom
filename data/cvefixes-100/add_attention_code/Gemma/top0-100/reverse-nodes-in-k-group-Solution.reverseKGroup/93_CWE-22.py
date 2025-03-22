def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def reverseKGroup(self, head, k):
    dummy = ListNode(-1)
    dummy.next = head

    cur, cur_dummy = head, dummy
    length = 0

    while cur:
        next_cur = cur.next
        length = (length + 1) % k

        if length == 0:
            next_dummy = cur_dummy.next
            self.reverse(cur_dummy, cur.next)
            cur_dummy = next_dummy

        cur = next_cur

    return dummy.next



