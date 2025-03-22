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

def getNewsFeed(self, userId):
    """
    Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
    :type userId: int
    :rtype: List[int]
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

    candidates = []
    if self.__messages[userId]:
        candidates.append((-self.__messages[userId][-1][0], userId, 0))
    for uid in self.__followings[userId]:
        if self.__messages[uid]:
            candidates.append((-self.__messages[uid][-1][0], uid, 0))
    nth_element(candidates, self.__number_of_most_recent_tweets-1)
    max_heap = candidates[:self.__number_of_most_recent_tweets]
    heapq.heapify(max_heap)
    result = []
    while max_heap and len(result) < self.__number_of_most_recent_tweets:
        t, uid, curr = heapq.heappop(max_heap)
        nxt = curr + 1
        if nxt != len(self.__messages[uid]):
            heapq.heappush(max_heap, (-self.__messages[uid][-(nxt+1)][0], uid, nxt))
        result.append(self.__messages[uid][-(curr+1)][1])
    return result



