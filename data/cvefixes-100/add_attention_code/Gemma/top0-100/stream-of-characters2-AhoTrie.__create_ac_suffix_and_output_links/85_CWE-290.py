def validate_agent_data(agent_data):
    if agent_data is None:
        return False, None

    # validate that the allowlist is proper JSON
    lists = json.loads(agent_data['allowlist'])

    # Validate exlude list contains valid regular expressions
    is_valid, _, err_msg = config.valid_exclude_list(lists.get('exclude'))
    if not is_valid:
        err_msg += " Exclude list regex is misformatted. Please correct the issue and try again."

    return is_valid, err_msg

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



