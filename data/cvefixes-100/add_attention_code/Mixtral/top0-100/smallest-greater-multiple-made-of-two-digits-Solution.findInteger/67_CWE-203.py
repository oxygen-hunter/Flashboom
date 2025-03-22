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

def findInteger(self, k, digit1, digit2):
    """
    :type k: int
    :type digit1: int
    :type digit2: int
    :rtype: int
    """
    MAX_NUM_OF_DIGITS = 10
    INT_MAX = 2**31-1

    if digit1 < digit2:
        digit1, digit2 = digit2, digit1
    total = 2
    for l in xrange(1, MAX_NUM_OF_DIGITS+1):
        for mask in xrange(total):
            curr, bit = 0, total>>1
            while bit:
                curr = curr*10 + (digit1 if mask&bit else digit2)
                bit >>= 1
            if k < curr <= INT_MAX and curr%k == 0:
                return curr
        total <<= 1
    return -1


