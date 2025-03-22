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

def stoneGameV(self, stoneValue):
    """
    :type stoneValue: List[int]
    :rtype: int
    """
    n = len(stoneValue)
    prefix = [0]
    for v in stoneValue:
        prefix.append(prefix[-1] + v)

    mid = [[0]*n for _ in xrange(n)]
    for l in xrange(1, n+1):
        for i in xrange(n-l+1):
            j = i+l-1
            p = i if l == 1 else mid[i][j-1]
            while prefix[p]-prefix[i] < prefix[j+1]-prefix[p]:
                p += 1  # Time: O(n^2) in total
            mid[i][j] = p
    
    rmq = [[0]*n for _ in xrange(n)]
    for i in xrange(n):
        rmq[i][i] = stoneValue[i]

    dp = [[0]*n for _ in xrange(n)]
    for l in xrange(2, n+1):
        for i in xrange(n-l+1):
            j = i+l-1
            p = mid[i][j]
            max_score = 0
            if prefix[p]-prefix[i] == prefix[j+1]-prefix[p]:
                max_score = max(rmq[i][p-1], rmq[j][p])
            else:
                if i <= p-2:
                    max_score = max(max_score, rmq[i][p-2])
                if p <= j:
                    max_score = max(max_score, rmq[j][p])
            dp[i][j] = max_score
            rmq[i][j] = max(rmq[i][j-1], (prefix[j+1]-prefix[i]) + max_score)
            rmq[j][i] = max(rmq[j][i+1], (prefix[j+1]-prefix[i]) + max_score)
    return dp[0][n-1]


