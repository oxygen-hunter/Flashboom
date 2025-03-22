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

def gameOfLife(self, board):
    """
    :type board: List[List[int]]
    :rtype: void Do not return anything, modify board in-place instead.
    """
    m = len(board)
    n = len(board[0]) if m else 0
    for i in xrange(m):
        for j in xrange(n):
            count = 0
            ## Count live cells in 3x3 block.
            for I in xrange(max(i-1, 0), min(i+2, m)):
                for J in xrange(max(j-1, 0), min(j+2, n)):
                    count += board[I][J] & 1

            # if (count == 4 && board[i][j]) means:
            #     Any live cell with three live neighbors lives.
            # if (count == 3) means:
            #     Any live cell with two live neighbors.
            #     Any dead cell with exactly three live neighbors lives.
            if (count == 4 and board[i][j]) or count == 3:
                board[i][j] |= 2  # Mark as live.

    for i in xrange(m):
        for j in xrange(n):
            board[i][j] >>= 1  # Update to the next state.



