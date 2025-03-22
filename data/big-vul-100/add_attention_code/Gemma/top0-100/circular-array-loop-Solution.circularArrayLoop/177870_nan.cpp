ztype(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    ref tnref;
    int code = array_get(imemory, op, (long)r_btype(op - 1), &tnref);

    if (code < 0)
        return code;
    if (!r_has_type(&tnref, t_name)) {
         /* Must be either a stack underflow or a t_[a]struct. */
         check_op(2);
         {                       /* Get the type name from the structure. */
            if (op[-1].value.pstruct != 0x00) {
             const char *sname =
                 gs_struct_type_name_string(gs_object_type(imemory,
                                                           op[-1].value.pstruct));
            int code = name_ref(imemory, (const byte *)sname, strlen(sname),
                                (ref *) (op - 1), 0);

            if (code < 0)
                return code;
            } else
                return_error(gs_error_stackunderflow);
        }
        r_set_attrs(op - 1, a_executable);
    } else {
        ref_assign(op - 1, &tnref);
    }
    pop(1);
    return 0;
}


    bool circularArrayLoop(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) {
                continue;
            }
            int slow = i, fast = i;
            while (nums[next(nums, slow)] * nums[i] > 0 &&
                   nums[next(nums, fast)] * nums[i] > 0 &&
                   nums[next(nums, next(nums, fast))] * nums[i] > 0) {

                slow = next(nums, slow);
                fast = next(nums, next(nums, fast));
                if (slow == fast) {
                    if (slow == next(nums, slow)) {
                        break;
                    }
                    return true;
                }
            }
            slow = i;
            int val = nums[i];
            while (nums[slow] * val > 0) {
                int tmp = next(nums, slow);
                nums[slow] = 0;
                slow = tmp;
            }
        }
        return false;
    }


