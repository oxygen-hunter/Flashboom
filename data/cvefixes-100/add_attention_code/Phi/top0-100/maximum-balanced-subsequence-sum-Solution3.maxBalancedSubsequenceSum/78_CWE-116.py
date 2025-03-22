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

def maxBalancedSubsequenceSum(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    NEG_INF = float("-inf")
    # Range Maximum Query
    class SegmentTree(object):
        def __init__(self, N,
                     build_fn=lambda _: None,
                     query_fn=lambda x, y: max(x, y),
                     update_fn=lambda x, y: max(x, y)):
            self.tree = [None]*(2*2**((N-1).bit_length()))
            self.base = len(self.tree)//2
            self.query_fn = query_fn
            self.update_fn = update_fn
            for i in xrange(self.base, self.base+N):
                self.tree[i] = build_fn(i-self.base)
            for i in reversed(xrange(1, self.base)):
                self.tree[i] = query_fn(self.tree[2*i], self.tree[2*i+1])

        def update(self, i, h):
            x = self.base+i
            self.tree[x] = self.update_fn(self.tree[x], h)
            while x > 1:
                x //= 2
                self.tree[x] = self.query_fn(self.tree[x*2], self.tree[x*2+1])

        def query(self, L, R):
            if L > R:
                return None
            L += self.base
            R += self.base
            left = right = None
            while L <= R:
                if L & 1:
                    left = self.query_fn(left, self.tree[L])
                    L += 1
                if R & 1 == 0:
                    right = self.query_fn(self.tree[R], right)
                    R -= 1
                L //= 2
                R //= 2
            return self.query_fn(left, right)

    val_to_idx = {x:i for i, x in enumerate(sorted({x-i for i, x in enumerate(nums)}))}
    st = SegmentTree(len(val_to_idx))
    for i, x in enumerate(nums):
        v = max(st.query(0, val_to_idx[x-i]), 0)+x
        st.update(val_to_idx[x-i], v)
    return st.query(0, len(val_to_idx)-1)


