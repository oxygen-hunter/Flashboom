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

def largestPalindrome(self, n, k):
    """
    :type n: int
    :type k: int
    :rtype: str
    """
    def inv(x, p):
        return pow(x, p-2, p)

    def f(l):
        p = 7
        result = ['9']*l
        if l:                
            curr = reduce(lambda accu, x: (accu*10+(ord(x)-ord('0')))%p, result, 0)
            # l%2 == 0: (curr+(i-9)*11*pow(10, l//2-1, p))%p = 0
            # l%2 == 1: (curr+(i-9)*pow(10, l//2, p))%p = 0
            i = 9-(curr*inv(11 if l%2 == 0 else 1, p)*inv(pow(10, l//2-int(l%2 == 0), p), p))%p
            if i <= 2:
                i += p
            result[l//2] = result[l//2-int(l%2 == 0)] = str(i)
        return "".join(result)

    if k in (1, 3, 9):
        return '9'*n
    if k in (2, 4, 8):
        k = min(k, 6)
        if n <= k:
            return '8'*n
        l = k//2
        return '8'*l+'9'*(n-k)+'8'*l
    if k == 5:
        if n <= 2:
            return '5'*n
        return '5'+'9'*(n-2)+'5'
    if k == 6:
        if n <= 2:
            return '6'*n
        if n%2:
            l = n//2-1
            return '8'+'9'*l+'8'+'9'*l+'8'
        l = n//2-2
        return '8'+'9'*l+"77"+'9'*l+'8'
    l, r = divmod(n, 12)
    return "999999"*l+f(r)+"999999"*l  # 999999%7 = 0


