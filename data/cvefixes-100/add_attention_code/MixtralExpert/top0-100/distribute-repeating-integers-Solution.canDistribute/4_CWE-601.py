def prepare(self, reactor, clock, hs):
    # build a replication server
    server_factory = ReplicationStreamProtocolFactory(hs)
    self.streamer = hs.get_replication_streamer()
    self.server = server_factory.buildProtocol(None)

    # Make a new HomeServer object for the worker
    self.reactor.lookups["testserv"] = "1.2.3.4"
    self.worker_hs = self.setup_test_homeserver(
        http_client=None,
        homeserver_to_use=GenericWorkerServer,
        config=self._get_worker_hs_config(),
        reactor=self.reactor,
    )

    # Since we use sqlite in memory databases we need to make sure the
    # databases objects are the same.
    self.worker_hs.get_datastore().db_pool = hs.get_datastore().db_pool

    self.test_handler = self._build_replication_data_handler()
    self.worker_hs._replication_data_handler = self.test_handler

    repl_handler = ReplicationCommandHandler(self.worker_hs)
    self.client = ClientReplicationStreamProtocol(
        self.worker_hs, "client", "test", clock, repl_handler,
    )

    self._client_transport = None
    self._server_transport = None

def canDistribute(self, nums, quantity):
    """
    :type nums: List[int]
    :type quantity: List[int]
    :rtype: bool
    """
    def nth_element(nums, n, compare=lambda a, b: a < b):
        def tri_partition(nums, left, right, target, compare):
            mid = left
            while mid <= right:
                if nums[mid] == target:
                    mid += 1
                elif compare(nums[mid], target):
                    nums[left], nums[mid] = nums[mid], nums[left]
                    left += 1
                    mid += 1
                else:
                    nums[mid], nums[right] = nums[right], nums[mid]
                    right -= 1
            return left, right

        left, right = 0, len(nums)-1
        while left <= right:
            pivot_idx = random.randint(left, right)
            pivot_left, pivot_right = tri_partition(nums, left, right, nums[pivot_idx], compare)
            if pivot_left <= n <= pivot_right:
                return
            elif pivot_left > n:
                right = pivot_left-1
            else:  # pivot_right < n.
                left = pivot_right+1

    count = collections.Counter(nums)
    total = (1<<len(quantity))-1
    requirement = [0]*(total+1)
    for mask in xrange(len(requirement)):  # Time: O(2^m)
        base = 1
        for i in xrange(len(quantity)):  # Time: O(m)
            if mask&base:
                requirement[mask] += quantity[i]
            base <<= 1
    dp = [[0]*(total+1) for _ in xrange(2)]
    dp[0][0] = 1
    i = 0
    cnts = count.values()
    if len(quantity) < len(cnts):  # at most use top m cnts
        nth_element(cnts, len(quantity)-1, lambda a, b: a > b)
        cnts = cnts[:len(quantity)]
    for cnt in cnts:  # Time: O(m)
        dp[(i+1)%2] = [0]*(total+1)
        # submask enumeration:
        # => sum(nCr(m, k) * 2^k for k in xrange(m+1)) = (1 + 2)^m = 3^m
        # => Time: O(3^m), see https://cp-algorithms.com/algebra/all-submasks.html
        for mask in reversed(xrange(total+1)):
            dp[(i+1)%2][mask] |= dp[i%2][mask]
            submask = mask
            while submask > 0:
                if requirement[submask] <= cnt and dp[i%2][mask^submask]:
                    dp[(i+1)%2][mask] = 1
                submask = (submask-1)&mask
        i += 1
    return dp[len(cnts)%2][total]


