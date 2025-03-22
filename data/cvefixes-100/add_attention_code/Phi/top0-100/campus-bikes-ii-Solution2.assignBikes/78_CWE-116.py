def prepare_plugin_docs_command(self, plugin_names, plugin_type=None, response_format=None,
                                snippet=False, playbook_dir=None, module_path=None):

    if response_format and response_format not in DocConfig._supported_response_formats:
        raise ConfigurationError("Invalid response_format {0}, valid value is one of either {1}".format(response_format,
                                                                                                        ", ".join(DocConfig._supported_response_formats)))

    if not isinstance(plugin_names, list):
        raise ConfigurationError("plugin_names should be of type list, instead received {0} of type {1}".format(plugin_names, type(plugin_names)))

    self._prepare_env(runner_mode=self.runner_mode)
    self.cmdline_args = []

    if response_format == 'json':
        self.cmdline_args.append('-j')

    if snippet:
        self.cmdline_args.append('-s')

    if plugin_type:
        self.cmdline_args.extend(['-t', plugin_type])

    if playbook_dir:
        self.cmdline_args.extend(['--playbook-dir', playbook_dir])

    if module_path:
        self.cmdline_args.extend(['-M', module_path])

    self.cmdline_args.append(" ".join(plugin_names))

    self.command = [self._ansible_doc_exec_path] + self.cmdline_args
    self._handle_command_wrap(self.execution_mode, self.cmdline_args)

def assignBikes(self, workers, bikes):
    """
    :type workers: List[List[int]]
    :type bikes: List[List[int]]
    :rtype: int
    """
    def manhattan(p1, p2):
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])
    
    min_heap = [(0, 0, 0)]
    lookup = set()
    while min_heap:
        cost, i, taken = heapq.heappop(min_heap)
        if (i, taken) in lookup:
            continue
        lookup.add((i, taken))
        if i == len(workers):
            return cost
        for j in xrange(len(bikes)):
            if taken & (1<<j):
                continue
            heapq.heappush(min_heap, (cost+manhattan(workers[i], bikes[j]),  # O(b)
                                      i+1,            # O(w)
                                      taken|(1<<j)))  # O(2^b)



