void aes_crypt_ecb( aes_context *ctx,
                    int mode,
                    const unsigned char input[16],
                    unsigned char output[16] )
{
    int i;
    unsigned long *RK, X0, X1, X2, X3, Y0, Y1, Y2, Y3;

#if defined(XYSSL_PADLOCK_C) && defined(XYSSL_HAVE_X86)
    if( padlock_supports( PADLOCK_ACE ) )
    {
        if( padlock_xcryptecb( ctx, mode, input, output ) == 0 )
            return;
     }
 #endif
 
     RK = ctx->rk;
 
     GET_ULONG_LE( X0, input,  0 ); X0 ^= *RK++;

    if( mode == AES_DECRYPT )
    {
        for( i = (ctx->nr >> 1) - 1; i > 0; i-- )
        {
            AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );
            AES_RROUND( X0, X1, X2, X3, Y0, Y1, Y2, Y3 );
        }

        AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );

        X0 = *RK++ ^ ( RSb[ ( Y0       ) & 0xFF ]       ) ^
                     ( RSb[ ( Y3 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( RSb[ ( Y2 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)RSb[ ( Y1 >> 24 ) & 0xFF ]) << 24 );

        X1 = *RK++ ^ ( RSb[ ( Y1       ) & 0xFF ]       ) ^
                     ( RSb[ ( Y0 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( RSb[ ( Y3 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)RSb[ ( Y2 >> 24 ) & 0xFF ]) << 24 );

        X2 = *RK++ ^ ( RSb[ ( Y2       ) & 0xFF ]       ) ^
                     ( RSb[ ( Y1 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( RSb[ ( Y0 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)RSb[ ( Y3 >> 24 ) & 0xFF ]) << 24 );

        X3 = *RK++ ^ ( RSb[ ( Y3       ) & 0xFF ]       ) ^
                     ( RSb[ ( Y2 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( RSb[ ( Y1 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)RSb[ ( Y0 >> 24 ) & 0xFF ]) << 24 );
    }
    else /* AES_ENCRYPT */
    {
        for( i = (ctx->nr >> 1) - 1; i > 0; i-- )
        {
            AES_FROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );
            AES_FROUND( X0, X1, X2, X3, Y0, Y1, Y2, Y3 );
        }

        AES_FROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );

        X0 = *RK++ ^ ( FSb[ ( Y0       ) & 0xFF ]       ) ^
                     ( FSb[ ( Y1 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( FSb[ ( Y2 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)FSb[ ( Y3 >> 24 ) & 0xFF ]) << 24 );

        X1 = *RK++ ^ ( FSb[ ( Y1       ) & 0xFF ]       ) ^
                     ( FSb[ ( Y2 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( FSb[ ( Y3 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)FSb[ ( Y0 >> 24 ) & 0xFF ]) << 24 );

        X2 = *RK++ ^ ( FSb[ ( Y2       ) & 0xFF ]       ) ^
                     ( FSb[ ( Y3 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( FSb[ ( Y0 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)FSb[ ( Y1 >> 24 ) & 0xFF ]) << 24 );

        X3 = *RK++ ^ ( FSb[ ( Y3       ) & 0xFF ]       ) ^
                     ( FSb[ ( Y0 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( FSb[ ( Y1 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)FSb[ ( Y2 >> 24 ) & 0xFF ]) << 24 );
    }

    PUT_ULONG_LE( X0, output,  0 );
    PUT_ULONG_LE( X1, output,  4 );
    PUT_ULONG_LE( X2, output,  8 );
    PUT_ULONG_LE( X3, output, 12 );
}

    int triangularSum(vector<int>& nums) {
        const auto& exp_mod = [](const auto& p, const auto& mod) {
            vector<int> result = {p};
            while (result.back() * p % 10 != result[0]) {
                 result.emplace_back(result.back() * p %10);
            }
            rotate(rbegin(result), rbegin(result) + 1, rend(result));
            return result;
        };
        const auto& inv_mod = [](const auto& x, const auto& mod) {
            int y = x;
            while (y * x % 10 != 1) {
                y = y * x % 10;
            }
            return y;
        };
        const auto& factor_p = [](auto x, const auto& p, auto cnt, auto diff) {
            if (x == 0) {
                return make_pair(x, cnt);
            }
            while (x % p == 0) {
                x /= p;
                cnt += diff;
            }
            return make_pair(x, cnt);
        };
    
        const unordered_map<int, vector<int>> EXP = {{2, exp_mod(2, 10)}, {5, exp_mod(5, 10)}};  // {2:[6, 2, 4, 8], 5:[5]}
        const unordered_map<int, int> INV = {{1, inv_mod(1, 10)}, {3, inv_mod(3, 10)}, {7, inv_mod(7, 10)}, {9, inv_mod(9, 10)}};  // {1:1, 3:7, 7:3, 9:9}
        int result = 0;
        int nCr = 1;
        unordered_map<int, int> cnt = {{2, 0}, {5, 0}};
        for (int i = 0; i < size(nums); ++i) {
            if (!cnt[2] && !cnt[5]) {
                result = (result + nCr * nums[i]) % 10;
            } else if (cnt[2] && !cnt[5]) {
                result = (result + nCr * EXP.at(2)[cnt[2] % size(EXP.at(2))] * nums[i]) % 10;
            } else if (!cnt[2] && cnt[5]) {
                result = (result + nCr*EXP.at(5)[cnt[5] % size(EXP.at(5))] * nums[i]) % 10;
            }
            int mul = (size(nums) - 1) - i;
            tie(mul, cnt[2]) = factor_p(mul, 2, cnt[2], 1);
            tie(mul, cnt[5]) = factor_p(mul, 5, cnt[5], 1);
            int div = i + 1;
            tie(div, cnt[2]) = factor_p(div, 2, cnt[2], -1);
            tie(div, cnt[5]) = factor_p(div, 5, cnt[5], -1);
            nCr = nCr * mul % 10;
            nCr = nCr * INV.at(div % 10) % 10;
        }
        return result;
    }

