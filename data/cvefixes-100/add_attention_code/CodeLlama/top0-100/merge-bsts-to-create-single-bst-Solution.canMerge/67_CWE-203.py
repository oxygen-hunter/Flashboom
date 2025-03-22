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

def canMerge(self, trees):
    """
    :type trees: List[TreeNode]
    :rtype: TreeNode
    """
    def find_leaves_and_roots(trees, leaf_vals_set, val_to_root):
        for root in trees:
            val_to_root[root.val] = root
            q = [root]
            while q:
                new_q = []
                for node in q:
                    if node.left is None and node.right is None:
                        if node is not root:
                            leaf_vals_set.add(node.val)
                        continue
                    if node.left:
                        new_q.append(node.left)
                    if node.right:
                        new_q.append(node.right)
                q = new_q

    def find_root(trees, left_vals_set, val_to_root):
        root = None
        for node in trees:
            if node.val in leaf_vals_set:
                continue
            if root:  # multiple roots
                return None
            root = node
        return root

    def merge_bsts(root, left_vals_set, val_to_root):
        if not root:
            return None
        del val_to_root[root.val]
        q = [(root, float("-inf"), float("inf"))]
        while q:
            new_q = []
            for node, left, right in q:
                if not (left < node.val < right):
                    return None
                if node.left:
                    if node.left.val in leaf_vals_set and node.left.val in val_to_root:
                        node.left = val_to_root[node.left.val]
                        del val_to_root[node.left.val]
                    new_q.append((node.left, left, node.val))
                if node.right:
                    if node.right.val in leaf_vals_set and node.right.val in val_to_root:
                        node.right = val_to_root[node.right.val]
                        del val_to_root[node.right.val]
                    new_q.append((node.right, node.val, right))
            q = new_q
        return root if not val_to_root else None

    leaf_vals_set, val_to_root = set(), {}
    find_leaves_and_roots(trees, leaf_vals_set, val_to_root)    
    root = find_root(trees, leaf_vals_set, val_to_root)
    return merge_bsts(root, leaf_vals_set, val_to_root)


