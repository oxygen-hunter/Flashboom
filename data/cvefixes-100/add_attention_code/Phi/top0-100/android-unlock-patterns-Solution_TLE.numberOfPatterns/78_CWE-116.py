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

def numberOfPatterns(self, m, n):
    """
    :type m: int
    :type n: int
    :rtype: int
    """
    def merge(used, i):
        return used | (1 << i)

    def contain(used, i):
        return bool(used & (1 << i))

    def convert(i, j):
        return 3 * i + j

    def numberOfPatternsHelper(m, n, level, used, i):
        number = 0
        if level > n:
            return number

        if m <= level <= n:
            number += 1

        x1, y1 = divmod(i, 3)
        for j in xrange(9):
            if contain(used, j):
                continue

            x2, y2 = divmod(j, 3)
            if ((x1 == x2 and abs(y1 - y2) == 2) or
                (y1 == y2 and abs(x1 - x2) == 2) or
                (abs(x1 - x2) == 2 and abs(y1 - y2) == 2)) and \
               not contain(used,
                           convert((x1 + x2) // 2, (y1 + y2) // 2)):
                    continue

            number += numberOfPatternsHelper(m, n, level + 1, merge(used, j), j)

        return number

    number = 0
    # 1, 3, 7, 9
    number += 4 * numberOfPatternsHelper(m, n, 1, merge(0, 0), 0)
    # 2, 4, 6, 8
    number += 4 * numberOfPatternsHelper(m, n, 1, merge(0, 1), 1)
    # 5
    number += numberOfPatternsHelper(m, n, 1, merge(0, 4), 4)
    return number



