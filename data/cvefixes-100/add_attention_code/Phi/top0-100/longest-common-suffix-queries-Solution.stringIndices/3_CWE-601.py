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

def stringIndices(self, wordsContainer, wordsQuery):
    """
    :type wordsContainer: List[str]
    :type wordsQuery: List[str]
    :rtype: List[int]
    """
    INF = float("INF")
    class Trie(object):
        def __init__(self):
            self.__nodes = []
            self.__mns = []
            self.__new_node()
        
        def __new_node(self):
            self.__nodes.append([-1]*26)
            self.__mns.append((INF, INF))
            return len(self.__nodes)-1

        def add(self, i, w):
            curr = 0
            self.__mns[curr] = min(self.__mns[curr], (len(w), i))
            for c in reversed(w):
                x = ord(c)-ord('a')
                if self.__nodes[curr][x] == -1:
                    self.__nodes[curr][x] = self.__new_node()
                curr = self.__nodes[curr][x]
                self.__mns[curr] = min(self.__mns[curr], (len(w), i))
        
        def query(self, w):
            curr = 0
            for c in reversed(w):
                x = ord(c)-ord('a')
                if self.__nodes[curr][x] == -1:
                    break
                curr = self.__nodes[curr][x]
            return self.__mns[curr][1]

    trie = Trie()
    for i, w in enumerate(wordsContainer): 
        trie.add(i, w)
    return [trie.query(w) for w in wordsQuery]


