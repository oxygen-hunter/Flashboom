static struct posix_acl *jffs2_get_acl(struct inode *inode, int type)
 {
        struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
        struct posix_acl *acl;
	char *value = NULL;
	int rc, xprefix;

	switch (type) {
	case ACL_TYPE_ACCESS:
		acl = jffs2_iget_acl(inode, &f->i_acl_access);
		if (acl != JFFS2_ACL_NOT_CACHED)
			return acl;
		xprefix = JFFS2_XPREFIX_ACL_ACCESS;
		break;
	case ACL_TYPE_DEFAULT:
		acl = jffs2_iget_acl(inode, &f->i_acl_default);
		if (acl != JFFS2_ACL_NOT_CACHED)
			return acl;
		xprefix = JFFS2_XPREFIX_ACL_DEFAULT;
		break;
	default:
		return ERR_PTR(-EINVAL);
	}
	rc = do_jffs2_getxattr(inode, xprefix, "", NULL, 0);
	if (rc > 0) {
		value = kmalloc(rc, GFP_KERNEL);
		if (!value)
			return ERR_PTR(-ENOMEM);
		rc = do_jffs2_getxattr(inode, xprefix, "", value, rc);
	}
	if (rc > 0) {
		acl = jffs2_acl_from_medium(value, rc);
	} else if (rc == -ENODATA || rc == -ENOSYS) {
		acl = NULL;
	} else {
		acl = ERR_PTR(rc);
	}
	if (value)
		kfree(value);
	if (!IS_ERR(acl)) {
		switch (type) {
		case ACL_TYPE_ACCESS:
			jffs2_iset_acl(inode, &f->i_acl_access, acl);
			break;
		case ACL_TYPE_DEFAULT:
			jffs2_iset_acl(inode, &f->i_acl_default, acl);
			break;
		}
	}
	return acl;
}


    int maxProfit(int k, vector<int> &prices) {
        vector<int> profits;
        vector<pair<int, int>> v_p_stk;  // mono stack, where v is increasing and p is strictly decreasing
        for (int v = -1, p = -1; p + 1 < size(prices);) { // at most O(n) peaks, so v_p_stk and profits are both at most O(n) space
            for (v = p + 1; v + 1 < size(prices); ++v) {
                if (prices[v] < prices[v + 1]) {
                    break;
                }
            }
            for (p = v; p + 1 < size(prices); ++p) {
                if (prices[p] > prices[p + 1]) {
                    break;
                }
            }
            while (!empty(v_p_stk) && (prices[v_p_stk.back().first] > prices[v])) {  // not overlapped
                const auto [last_v, last_p] = move(v_p_stk.back()); v_p_stk.pop_back();
                profits.emplace_back(prices[last_p] - prices[last_v]);  // count [prices[last_v], prices[last_p]] interval
            }
            while (!empty(v_p_stk) && (prices[v_p_stk.back().second] <= prices[p])) {  // overlapped
                // prices[last_v] <= prices[v] <= prices[last_p] <= prices[p],
                // treat overlapped as [prices[v], prices[last_p]], [prices[last_v], prices[p]] intervals due to invariant max profit
                const auto [last_v, last_p] = move(v_p_stk.back()); v_p_stk.pop_back();
                profits.emplace_back(prices[last_p] - prices[v]);  // count [prices[v], prices[last_p]] interval
                v = last_v;  
            }
            v_p_stk.emplace_back(v, p);  // keep [prices[last_v], prices[p]] interval to check overlapped
        }        
        while (!empty(v_p_stk))  {
            const auto [last_v, last_p] = move(v_p_stk.back()); v_p_stk.pop_back();
            profits.emplace_back(prices[last_p] - prices[last_v]);  // count [prices[last_v], prices[last_p]] interval
        }
        if (k > size(profits)) {
            k = size(profits);
        } else {
            nth_element(begin(profits), begin(profits) + k - 1, end(profits), greater<int>());
        }
        return accumulate(cbegin(profits), cbegin(profits) + k, 0);  // top k profits of nonoverlapped intervals
    }


