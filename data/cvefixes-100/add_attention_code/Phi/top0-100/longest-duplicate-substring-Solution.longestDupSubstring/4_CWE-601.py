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

def longestDupSubstring(self, S):
    """
    :type S: str
    :rtype: str
    """
    M = 10**9+7
    D = 26

    def check(S, L):
        p = pow(D, L, M)
        curr = reduce(lambda x, y: (D*x+ord(y)-ord('a')) % M, S[:L], 0)
        lookup = collections.defaultdict(list)
        lookup[curr].append(L-1)
        for i in xrange(L, len(S)):
            curr = ((D*curr) % M + ord(S[i])-ord('a') -
                    ((ord(S[i-L])-ord('a'))*p) % M) % M
            if curr in lookup:
                for j in lookup[curr]:  # check if string is the same when hash is the same
                    if S[j-L+1:j+1] == S[i-L+1:i+1]:
                        return i-L+1
            lookup[curr].append(i)
        return 0

    left, right = 1, len(S)-1
    while left <= right:
        mid = left + (right-left)//2
        if not check(S, mid):
            right = mid-1
        else:
            left = mid+1
    result = check(S, right)
    return S[result:result + right]


