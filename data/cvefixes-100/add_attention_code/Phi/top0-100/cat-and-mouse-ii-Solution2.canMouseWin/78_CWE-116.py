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

def canMouseWin(self, grid, catJump, mouseJump):
    """
    :type grid: List[str]
    :type catJump: int
    :type mouseJump: int
    :rtype: bool
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    DRAW, MOUSE, CAT = range(3)
    def parents(m, c, t):
        if t == CAT:
            for nm in graph[m, MOUSE^CAT^t]:
                yield nm, c, MOUSE^CAT^t
        else:
            for nc in graph[c, MOUSE^CAT^t]:
                yield m, nc, MOUSE^CAT^t

    R, C = len(grid), len(grid[0])
    N = R*C
    WALLS = set()
    FOOD, MOUSE_START, CAT_START = [-1]*3
    for r in xrange(R):
        for c in xrange(C):
            if grid[r][c] == 'M':
                MOUSE_START = r*C + c
            elif grid[r][c] == 'C':
                CAT_START = r*C + c
            elif grid[r][c] == 'F':
                FOOD = r*C + c
            elif grid[r][c] == '#':
                WALLS.add(r*C + c)
    graph = collections.defaultdict(set)
    jump = {MOUSE:mouseJump, CAT:catJump}
    for r in xrange(R):
        for c in xrange(C):
            if grid[r][c] == '#':
                continue
            pos = r*C + c
            for t in [MOUSE, CAT]:
                for dr, dc in directions:
                    for d in xrange(jump[t]+1):
                        nr, nc = r+dr*d, c+dc*d
                        if not (0 <= nr < R and 0 <= nc < C and grid[nr][nc] != '#'):
                            break
                        graph[pos, t].add(nr*C + nc)

    degree = {}
    for m in xrange(N):
        for c in xrange(N):
            # degree[m, c, MOUSE] = len(graph[m, MOUSE])
            degree[m, c, CAT] = len(graph[c, CAT])
    color = collections.defaultdict(int)
    q1 = collections.deque()
    # q2 = collections.deque()
    for i in xrange(N):
        if i in WALLS or i == FOOD:
            continue
        color[FOOD, i, CAT] = MOUSE
        q1.append((FOOD, i, CAT))
        color[i, FOOD, MOUSE] = CAT
        # q2.append((i, FOOD, MOUSE))
        for t in [MOUSE, CAT]:
            color[i, i, t] = CAT
            # q2.append((i, i, t))
    while q1:
        i, j, t = q1.popleft()
        for ni, nj, nt in parents(i, j, t):
            if color[ni, nj, nt] != DRAW:
                continue
            if t == CAT:
                color[ni, nj, nt] = MOUSE
                q1.append((ni, nj, nt))
                continue
            degree[ni, nj, nt] -= 1
            if not degree[ni, nj, nt]:
                color[ni, nj, nt] = MOUSE
                q1.append((ni, nj, nt))
    # while q2:
    #     i, j, t = q2.popleft()
    #     for ni, nj, nt in parents(i, j, t):
    #         if color[ni, nj, nt] != DRAW:
    #             continue
    #         if t == MOUSE:
    #             color[ni, nj, nt] = CAT
    #             q2.append((ni, nj, nt))
    #             continue
    #         degree[ni, nj, nt] -= 1
    #         if not degree[ni, nj, nt]:
    #             color[ni, nj, nt] = CAT
    #             q2.append((ni, nj, nt))
    return color[MOUSE_START, CAT_START, MOUSE] == MOUSE


