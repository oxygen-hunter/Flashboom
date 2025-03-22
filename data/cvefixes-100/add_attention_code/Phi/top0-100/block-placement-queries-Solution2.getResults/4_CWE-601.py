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

def getResults(self, queries):
    """
    :type queries: List[List[int]]
    :rtype: List[bool]
    """
    # Template:
    # https://github.com/kamyu104/LeetCode-Solutions/blob/master/Python/booking-concert-tickets-in-groups.py
    class SegmentTree(object):
        def __init__(self, N,
                    build_fn=lambda _: None,
                    query_fn=lambda x, y: y if x is None else x if y is None else max(x, y),
                    update_fn=lambda x: x):
            self.tree = [None]*(1<<((N-1).bit_length()+1))
            self.base = len(self.tree)>>1
            self.query_fn = query_fn
            self.update_fn = update_fn
            for i in xrange(self.base, self.base+N):
                self.tree[i] = build_fn(i-self.base)
            for i in reversed(xrange(1, self.base)):
                self.tree[i] = query_fn(self.tree[i<<1], self.tree[(i<<1)+1])

        def update(self, i, h):
            x = self.base+i
            self.tree[x] = self.update_fn(h)
            while x > 1:
                x >>= 1
                self.tree[x] = self.query_fn(self.tree[x<<1], self.tree[(x<<1)+1])

        def query(self, L, R):
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
                L >>= 1
                R >>= 1
            return self.query_fn(left, right)

    def update(x):
        sl.add(x)
        i = sl.bisect_left(x)
        st.update(val_to_idx[x], x-(sl[i-1] if i-1 >= 0 else 0))
        if i+1 < len(sl):
            st.update(val_to_idx[sl[i+1]], sl[i+1]-x)
        
    val_to_idx = {x:i for i, x in enumerate(sorted(q[1] for q in queries if q[0] == 1))}
    st = SegmentTree(len(val_to_idx))
    sl = SortedList()
    result = []
    for q in queries:
        if q[0] == 1:
            update(q[1])
        else:
            i = sl.bisect_left(q[1])
            result.append(q[1]-(sl[i-1] if i-1 >= 0 else 0) >= q[2] or (i-1 >= 0 and st.query(0, val_to_idx[sl[i-1]]) >= q[2]))
    return result


