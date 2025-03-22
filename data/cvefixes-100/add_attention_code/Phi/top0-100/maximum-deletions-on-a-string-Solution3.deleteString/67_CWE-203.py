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

def deleteString(self, s):
    """
    :type s: str
    :rtype: int
    """
    MOD, P = 10**9+7, (113, 109)
    def hash(i, j):
        return [(prefix[idx][j+1]-prefix[idx][i]*power[idx][j-i+1])%MOD for idx in xrange(len(P))]

    if all(x == s[0] for x in s):
        return len(s)

    power = [[1] for _ in xrange(len(P))]
    prefix = [[0] for _ in xrange(len(P))]
    for x in s:
        for idx, p in enumerate(P):
            power[idx].append((power[idx][-1]*p)%MOD)
            prefix[idx].append((prefix[idx][-1]*p+(ord(x)-ord('a')))%MOD)
    dp = [1]*len(s)  # dp[i]: max operation count of s[i:]
    for i in reversed(xrange(len(s)-1)):
        for j in xrange(1, (len(s)-i)//2+1):
            if hash(i, i+j-1) == hash(i+j, i+2*j-1):
                dp[i] = max(dp[i], dp[i+j]+1)
    return dp[0]


