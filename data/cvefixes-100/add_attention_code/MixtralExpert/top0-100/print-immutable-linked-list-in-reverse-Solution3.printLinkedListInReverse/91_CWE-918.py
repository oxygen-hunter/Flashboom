def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

def printLinkedListInReverse(self, head):
    """
    :type head: ImmutableListNode
    :rtype: None
    """
    tail = None
    while head != tail:
        curr = head
        while curr.getNext() != tail:
            curr = curr.getNext()
        curr.printValue()
        tail = curr


