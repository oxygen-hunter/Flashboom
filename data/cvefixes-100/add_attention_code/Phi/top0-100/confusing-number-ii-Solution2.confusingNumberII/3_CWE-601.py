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

def confusingNumberII(self, n):
    """
    :type n: int
    :rtype: int
    """
    lookup = {"0":"0", "1":"1", "6":"9", "8":"8", "9":"6"}
    centers = {"0":"0", "1":"1", "8":"8"}
    def totalCount(n):  # count all numbers in the pattern of [01689]{1,len(n)} in the range of [0, n]
        s = str(n)
        total = 0 
        p = len(lookup)**(len(s)-1)
        for i in xrange(len(s)+1):
            if i == len(s):
                total += 1
                break
            smaller = sum(int(c < s[i]) for c in lookup.iterkeys())
            total += smaller * p
            if s[i] not in lookup:
                break
            p //= len(lookup)
        return total

    def validCountInLessLength(n):  # count unconfusing numbers in the pattern of [01689]{1,len(n)-1} in the range of [0, n]
        s = str(n)
        valid = 0
        total = len(centers)
        for i in xrange(1, len(s), 2):  # count unconfusing numbers for each odd length less than s
            if i == 1:
                valid += len(centers)
            else:
                valid += total * (len(lookup)-1)
                total *= len(lookup)
        total = 1
        for i in xrange(2, len(s), 2):  # count unconfusing numbers for each even length less than s
            valid += total * (len(lookup)-1)
            total *= len(lookup)
        return valid

    def validCountInFullLength(n):  # count unconfusing numbers in the pattern of [01689]{len(n)} in the range of [0, n]
        s = str(n)
        half_s = s[:(len(s)+1)//2]
        total = 0
        choices = centers if (len(s) % 2) else lookup
        p = int(len(lookup)**(len(half_s)-2) * len(choices))
        for i in xrange(len(half_s)):
            if i == len(half_s)-1:
                total += sum(int(c < half_s[i]) for c in choices.iterkeys() if len(s) != 2 or c != '0')
                if half_s[i] not in choices:
                    break
                tmp = list(half_s)+[lookup[half_s[i]] for i in reversed(xrange(len(half_s)-(len(s) % 2)))]
                total += int("".join(tmp)) <= n
                break
            smaller = sum(int(c < half_s[i]) for c in lookup.iterkeys() if i != 0 or c != '0')
            total += smaller * p
            if half_s[i] not in lookup:
                break
            p //= len(lookup)
        return total

    def f(n):  # count confusing numbers in the range of [0, n]
        return totalCount(n) - validCountInLessLength(n) - validCountInFullLength(n)

    return f(n) - f(0)  # f(0) is always 0 and could be ignored


