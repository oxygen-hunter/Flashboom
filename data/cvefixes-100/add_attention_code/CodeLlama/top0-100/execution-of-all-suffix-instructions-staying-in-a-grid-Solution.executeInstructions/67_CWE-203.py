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

def executeInstructions(self, n, startPos, s):
    """
    :type n: int
    :type startPos: List[int]
    :type s: str
    :rtype: List[int]
    """
    directions = {'U':(-1, 0), 'R':(0, 1), 'D':(1, 0), 'L':(0, -1)}
    (x0, y0), (x, y) = startPos, (0, 0)
    result = range(len(s), 0, -1)
    lookup_x = collections.defaultdict(list)
    lookup_y = collections.defaultdict(list)
    lookup_x[x0-x].append(0)
    lookup_y[y0-y].append(0)
    for i, d in enumerate(s):
        dx, dy = directions[d]
        x, y = x+dx, y+dy
        for k in n-x, -x-1:
            if k not in lookup_x:
                continue
            for j in lookup_x[k]:
                result[j] = min(result[j], i-j)
            lookup_x[k] = []
        for k in n-y, -y-1:
            if k not in lookup_y:
                continue
            for j in lookup_y[k]:
                result[j] = min(result[j], i-j)
            lookup_y[k] = []
        lookup_x[x0-x].append(i+1)
        lookup_y[y0-y].append(i+1)
    return result


