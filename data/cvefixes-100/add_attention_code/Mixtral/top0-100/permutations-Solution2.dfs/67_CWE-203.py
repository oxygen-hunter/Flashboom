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

def dfs(self, nums, path, res):
    if not nums:
        res.append(path)

    for i in xrange(len(nums)):
        # e.g., [1, 2, 3]: 3! = 6 cases
        # idx -> nums, path
        # 0 -> [2, 3], [1] -> 0: [3], [1, 2] -> [], [1, 2, 3]
        #                  -> 1: [2], [1, 3] -> [], [1, 3, 2]
        #
        # 1 -> [1, 3], [2] -> 0: [3], [2, 1] -> [], [2, 1, 3]
        #                  -> 1: [1], [2, 3] -> [], [2, 3, 1]
        #
        # 2 -> [1, 2], [3] -> 0: [2], [3, 1] -> [], [3, 1, 2]
        #                  -> 1: [1], [3, 2] -> [], [3, 2, 1]
        self.dfs(nums[:i] + nums[i+1:], path + [nums[i]], res)


