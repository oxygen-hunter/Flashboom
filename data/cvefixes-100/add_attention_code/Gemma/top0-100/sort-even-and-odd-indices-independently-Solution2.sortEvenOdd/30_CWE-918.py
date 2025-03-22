def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def sortEvenOdd(self, nums):
    """
    :type nums: List[int]
    :rtype: List[int]
    """
    def partition(index, nums):
        for i in xrange(len(nums)):
            j = i
            while nums[i] >= 0:
                j = index(j)
                nums[i], nums[j] = nums[j], ~nums[i]  # processed
        for i in xrange(len(nums)):
            nums[i] = ~nums[i]  # restore values
    
    partition(lambda i: i//2 if i%2 == 0 else (len(nums)+1)//2+i//2, nums)
    nums[:(len(nums)+1)//2], nums[(len(nums)+1)//2:] = sorted(nums[:(len(nums)+1)//2]), sorted(nums[(len(nums)+1)//2:], reverse=True)
    partition(lambda i: 2*i if i < (len(nums)+1)//2 else 1+2*(i-(len(nums)+1)//2), nums)
    return nums



