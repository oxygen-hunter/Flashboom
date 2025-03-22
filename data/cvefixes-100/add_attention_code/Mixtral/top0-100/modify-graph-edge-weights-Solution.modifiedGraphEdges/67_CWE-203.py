def gateway_postprocess(transaction, payment):
    if not transaction.is_success:
        return

    if transaction.action_required:
        payment.to_confirm = True
        payment.save(update_fields=["to_confirm"])
        return

    transaction_kind = transaction.kind
    # if transaction.action_required:
    #     payment.charge_status = ChargeStatus.ACTION_REQUIRED
    #     payment.save(update_fields=["charge_status", ])

    if transaction_kind in {TransactionKind.CAPTURE, TransactionKind.CONFIRM}:
        payment.captured_amount += transaction.amount

        # Set payment charge status to fully charged
        # only if there is no more amount needs to charge
        payment.charge_status = ChargeStatus.PARTIALLY_CHARGED
        if payment.get_charge_amount() <= 0:
            payment.charge_status = ChargeStatus.FULLY_CHARGED

        payment.save(update_fields=["charge_status", "captured_amount", "modified"])

    elif transaction_kind == TransactionKind.VOID:
        payment.is_active = False
        payment.save(update_fields=["is_active", "modified"])

    elif transaction_kind == TransactionKind.REFUND:
        changed_fields = ["captured_amount", "modified"]
        payment.captured_amount -= transaction.amount
        payment.charge_status = ChargeStatus.PARTIALLY_REFUNDED
        if payment.captured_amount <= 0:
            payment.charge_status = ChargeStatus.FULLY_REFUNDED
            payment.is_active = False
        changed_fields += ["charge_status", "is_active"]
        payment.save(update_fields=changed_fields)
    elif transaction_kind == TransactionKind.PENDING:
        payment.charge_status = ChargeStatus.PENDING
        payment.save(
            update_fields=["charge_status",]
        )

def modifiedGraphEdges(self, n, edges, source, destination, target):
    """
    :type n: int
    :type edges: List[List[int]]
    :type source: int
    :type destination: int
    :type target: int
    :rtype: List[List[int]]
    """
    def dijkstra(start, x):
        best = [target+1]*len(adj)
        best[start] = 0
        min_heap = [(0, start)]
        while min_heap:
            curr, u = heapq.heappop(min_heap)
            if curr > best[u]:
                continue
            for v, w in adj[u]:       
                if w == -1:
                    w = x
                if curr+w >= best[v]:
                    continue
                best[v] = curr+w
                heapq.heappush(min_heap, (best[v], v))
        return best
    
    adj = [[] for _ in xrange(n)]
    for u, v, w in edges:
        adj[u].append((v, w))
        adj[v].append((u, w))
    left = dijkstra(source, 1)
    if not (left[destination] <= target):
        return []
    right= dijkstra(destination, target+1)
    if not (right[source] >= target):
        return []
    for e in edges:
        if e[2] == -1:
            e[2] = max(target-left[e[0]]-right[e[1]], target-left[e[1]]-right[e[0]], 1)
    return edges


