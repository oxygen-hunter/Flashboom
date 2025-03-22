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

def getBiggestThree(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: List[int]
    """	
    K = 3
    left = [[grid[i][j] for j in xrange(len(grid[i]))] for i in xrange(len(grid))]
    right = [[grid[i][j] for j in xrange(len(grid[i]))] for i in xrange(len(grid))]
    for i in xrange(1, len(grid)):
        for j in xrange(len(grid[0])-1):
            left[i][j] += left[i-1][j+1]
    for i in xrange(1, len(grid)):
        for j in xrange(1, len(grid[0])):
            right[i][j] += right[i-1][j-1]
    min_heap = []
    lookup = set()
    for k in xrange((min(len(grid), len(grid[0]))+1)//2):
        for i in xrange(k, len(grid)-k):
            for j in xrange(k, len(grid[0])-k):
                total = (((left[i][j-k]-left[i-k][j])+(right[i][j+k]-right[i-k][j])+grid[i-k][j]) +  
                         ((left[i+k][j]-left[i][j+k])+(right[i+k][j]-right[i][j-k])-grid[i+k][j])) if k else grid[i][j]
                if total in lookup:
                    continue
                lookup.add(total)
                heapq.heappush(min_heap, total)
                if len(min_heap) == K+1:                        
                    lookup.remove(heapq.heappop(min_heap))
    min_heap.sort(reverse=True)
    return min_heap


