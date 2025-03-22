def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

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



