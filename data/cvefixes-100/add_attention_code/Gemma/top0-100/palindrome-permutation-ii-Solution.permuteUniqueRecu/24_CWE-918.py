def language_overview():
    if current_user.check_visibility(constants.SIDEBAR_LANGUAGE) and current_user.filter_language() == u"all":
        order_no = 0 if current_user.get_view_property('language', 'dir') == 'desc' else 1
        charlist = list()
        languages = calibre_db.speaking_language(reverse_order=not order_no, with_count=True)
        for lang in languages:
            upper_lang = lang[0].name[0].upper()
            if upper_lang not in charlist:
                charlist.append(upper_lang)
        return render_title_template('languages.html', languages=languages,
                                     charlist=charlist, title=_(u"Languages"), page="langlist",
                                     data="language", order=order_no)
    else:
        abort(404)

def permuteUniqueRecu(self, mid, result, used, cur, nums):
    if len(cur) == len(nums):
        half_palindrome = ''.join(cur)
        result.append(half_palindrome + mid + half_palindrome[::-1])
        return
    for i in xrange(len(nums)):
        if not used[i] and not (i > 0 and nums[i-1] == nums[i] and used[i-1]):
            used[i] = True
            cur.append(nums[i])
            self.permuteUniqueRecu(mid, result, used, cur, nums)
            cur.pop()
            used[i] = False



