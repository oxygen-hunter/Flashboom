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

def maximumStrongPairXor(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    result = 0
    for i in reversed(xrange(max(nums).bit_length())):
        prefix_min, prefix_max = {}, {}
        for x in nums:
            y = x>>i
            if y not in prefix_min:
                prefix_min[y] = prefix_max[y] = x
            prefix_min[y] = min(prefix_min[y], x)
            prefix_max[y] = max(prefix_max[y], x)
        result <<= 1
        for x in prefix_min.iterkeys():
            y = (result|1)^x
            assert(x != y)
            if y in prefix_max and prefix_min[max(x, y)] <= 2*prefix_max[min(x, y)]:
                result |= 1
                break
    return result



