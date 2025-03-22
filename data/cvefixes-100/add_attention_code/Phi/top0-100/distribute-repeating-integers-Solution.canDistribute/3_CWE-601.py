def make_worker_hs(
    self, worker_app: str, extra_config: dict = {}, **kwargs
) -> HomeServer:
    """Make a new worker HS instance, correctly connecting replcation
    stream to the master HS.

    Args:
        worker_app: Type of worker, e.g. `synapse.app.federation_sender`.
        extra_config: Any extra config to use for this instances.
        **kwargs: Options that get passed to `self.setup_test_homeserver`,
            useful to e.g. pass some mocks for things like `http_client`

    Returns:
        The new worker HomeServer instance.
    """

    config = self._get_worker_hs_config()
    config["worker_app"] = worker_app
    config.update(extra_config)

    worker_hs = self.setup_test_homeserver(
        homeserver_to_use=GenericWorkerServer,
        config=config,
        reactor=self.reactor,
        **kwargs,
    )

    # If the instance is in the `instance_map` config then workers may try
    # and send HTTP requests to it, so we register it with
    # `_handle_http_replication_attempt` like we do with the master HS.
    instance_name = worker_hs.get_instance_name()
    instance_loc = worker_hs.config.worker.instance_map.get(instance_name)
    if instance_loc:
        # Ensure the host is one that has a fake DNS entry.
        if instance_loc.host not in self.reactor.lookups:
            raise Exception(
                "Host does not have an IP for instance_map[%r].host = %r"
                % (instance_name, instance_loc.host,)
            )

        self.reactor.add_tcp_client_callback(
            self.reactor.lookups[instance_loc.host],
            instance_loc.port,
            lambda: self._handle_http_replication_attempt(
                worker_hs, instance_loc.port
            ),
        )

    store = worker_hs.get_datastore()
    store.db_pool._db_pool = self.database_pool._db_pool

    # Set up TCP replication between master and the new worker if we don't
    # have Redis support enabled.
    if not worker_hs.config.redis_enabled:
        repl_handler = ReplicationCommandHandler(worker_hs)
        client = ClientReplicationStreamProtocol(
            worker_hs, "client", "test", self.clock, repl_handler,
        )
        server = self.server_factory.buildProtocol(None)

        client_transport = FakeTransport(server, self.reactor)
        client.makeConnection(client_transport)

        server_transport = FakeTransport(client, self.reactor)
        server.makeConnection(server_transport)

    # Set up a resource for the worker
    resource = ReplicationRestResource(worker_hs)

    for servlet in self.servlets:
        servlet(worker_hs, resource)

    self._hs_to_site[worker_hs] = SynapseSite(
        logger_name="synapse.access.http.fake",
        site_tag="{}-{}".format(
            worker_hs.config.server.server_name, worker_hs.get_instance_name()
        ),
        config=worker_hs.config.server.listeners[0],
        resource=resource,
        server_version_string="1",
    )

    if worker_hs.config.redis.redis_enabled:
        worker_hs.get_tcp_replication().start_replication(worker_hs)

    return worker_hs

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


