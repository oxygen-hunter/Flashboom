def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def __create_ac_suffix_and_output_links(self, root):  # Time:  O(n + p^2), Space: O(t + p^2)
    queue = collections.deque()
    for node in root.children.itervalues():
        queue.append(node)
        node.suffix = root

    while queue:
        node = queue.popleft()
        for c, child in node.children.iteritems():
            queue.append(child)
            suffix = node.suffix
            while suffix and c not in suffix.children:
                suffix = suffix.suffix
            child.suffix = suffix.children[c] if suffix else root
            child.outputs += child.suffix.outputs  # Time: O(p^2)
    
    return root



