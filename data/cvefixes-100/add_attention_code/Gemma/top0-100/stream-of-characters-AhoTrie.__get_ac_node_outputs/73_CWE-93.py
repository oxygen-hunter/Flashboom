def replace(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                                str(value)]

def __get_ac_node_outputs(self, node):  # Time:  O(z), in this question, it could be improved to O(1)
                                        # if we only return a matched pattern without all matched ones
    result = []
    for i in node.indices:
        result.append(i)
        # return result
    output = node.output
    while output:
        for i in output.indices:
            result.append(i)
            # return result
        output = output.output
    return result



