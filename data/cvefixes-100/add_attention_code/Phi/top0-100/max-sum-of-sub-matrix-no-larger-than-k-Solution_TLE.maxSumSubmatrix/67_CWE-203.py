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

def maxSumSubmatrix(self, matrix, k):
    """
    :type matrix: List[List[int]]
    :type k: int
    :rtype: int
    """
    class BST(object):  # not avl, rbtree
        def __init__(self, val):
            self.val = val
            self.left = None
            self.right = None

        def insert(self, val):  # Time: O(h) = O(logn) ~ O(n)
            curr = self
            while curr:
                if curr.val >= val:
                    if curr.left:
                        curr = curr.left
                    else:
                        curr.left = BST(val)
                        return
                else:
                    if curr.right:
                        curr = curr.right
                    else:
                        curr.right = BST(val)
                        return

        def lower_bound(self, val):  # Time: O(h) = O(logn) ~ O(n)
            result, curr = None, self
            while curr:
                if curr.val >= val:
                    result, curr = curr, curr.left
                else:
                    curr = curr.right
            return result


    if not matrix:
        return 0

    m = min(len(matrix), len(matrix[0]))
    n = max(len(matrix), len(matrix[0]))
    result = float("-inf")

    for i in xrange(m):
        sums = [0] * n
        for j in xrange(i, m):
            for l in xrange(n):
                sums[l] += matrix[j][l] if m == len(matrix) else matrix[l][j]

            # Find the max subarray no more than K.
            accu_sum_set = BST(0)
            accu_sum = 0
            for sum in sums:
                accu_sum += sum
                node = accu_sum_set.lower_bound(accu_sum - k)
                if node:
                    result = max(result, accu_sum - node.val)
                accu_sum_set.insert(accu_sum)

    return result



