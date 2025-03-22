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

def reorderSpaces(self, text):
    """
    :type text: str
    :rtype: str
    """
    text = list(text)
    # count the spaces and words
    space_count, word_count = 0, 0
    for i, c in enumerate(text):
        if c == ' ':
            space_count += 1
        elif i == 0 or text[i-1] == ' ':
            word_count += 1

    # rearrange all the spaces to the right
    left, i = 0, 0
    while i < len(text):
        has_word = False
        while i < len(text) and text[i] != ' ':
            text[left], text[i] = text[i], text[left]
            left += 1
            i += 1
            has_word = True
        if has_word:
            left += 1  # keep one space
        i += 1

    # rearrange all the spaces to the left
    equal_count = space_count//(word_count-1) if word_count-1 > 0 else 0
    extra_count = space_count%(word_count-1) if word_count-1 > 0 else space_count
    right, i = len(text)-1-extra_count, len(text)-1
    while i >= 0:
        has_word = False
        while i >= 0 and text[i] != ' ':
            text[right], text[i] = text[i], text[right]
            right -= 1
            i -= 1
            has_word = True
        if has_word:
            right -= equal_count  # keep equal_count spaces
        i -= 1
    return "".join(text)


