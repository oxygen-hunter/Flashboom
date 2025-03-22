def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

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



