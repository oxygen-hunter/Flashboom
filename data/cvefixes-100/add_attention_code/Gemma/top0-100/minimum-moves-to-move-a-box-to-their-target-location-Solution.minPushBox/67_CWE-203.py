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

def minPushBox(self, grid):
    """
    :type grid: List[List[str]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    def dot(a, b):
        return a[0]*b[0]+a[1]*b[1]

    def can_reach(grid, b, p, t):
        closer, detour = [p], []
        lookup = set([b])
        while closer or detour:
            if not closer:
                closer, detour = detour, closer
            p = closer.pop()
            if p == t:
                return True
            if p in lookup:
                continue
            lookup.add(p)
            for dx, dy in directions:
                np = (p[0]+dx, p[1]+dy)
                if not (0 <= np[0] < len(grid) and 0 <= np[1] < len(grid[0]) and
                   grid[np[0]][np[1]] != '#' and np not in lookup):
                    continue
                (closer if dot((dx, dy), (t[0]-p[0], t[1]-p[1])) > 0 else detour).append(np)
        return False

    def g(a, b):
        return abs(a[0]-b[0])+abs(a[1]-b[1])
    
    def a_star(grid, b, p, t):
        f, dh = g(b, t), 2
        closer, detour = [(b, p)], []
        lookup = set()
        while closer or detour:
            if not closer:
                f += dh
                closer, detour = detour, closer
            b, p = closer.pop()
            if b == t:
                return f
            if (b, p) in lookup:
                continue
            lookup.add((b, p))
            for dx, dy in directions:
                nb, np = (b[0]+dx, b[1]+dy), (b[0]-dx, b[1]-dy)
                if not (0 <= nb[0] < len(grid) and 0 <= nb[1] < len(grid[0]) and
                        0 <= np[0] < len(grid) and 0 <= np[1] < len(grid[0]) and
                        grid[nb[0]][nb[1]] != '#' and grid[np[0]][np[1]] != '#' and
                        (nb, b) not in lookup and can_reach(grid, b, p, np)):
                    continue
                (closer if dot((dx, dy), (t[0]-b[0], t[1]-b[1])) > 0 else detour).append((nb, b))
        return -1
    
    b, p, t = None, None, None
    for i in xrange(len(grid)):
        for j in xrange(len(grid[0])):
            if grid[i][j] == 'B':
                b = (i, j)
            elif grid[i][j] == 'S':
                p = (i, j)
            elif grid[i][j] == 'T':
                t = (i, j)
    return a_star(grid, b, p, t)


