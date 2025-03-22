def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

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



