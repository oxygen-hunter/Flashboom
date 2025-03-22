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

    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        vector<vector<int>> adj(size(cost));
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1]);
            adj[e[1]].emplace_back(e[0]);
        }
        vector<long long> result(size(cost));
        const auto& iter_dfs = [&]() {
            vector<long long> result(size(cost));
            using RET = vector<int64_t>;
            RET ret = {cost[0]};
            vector<tuple<int, int, int, int, shared_ptr<RET>, RET *>> stk = {{1, 0, -1, -1, nullptr, &ret}};
            while (!stk.empty()) {
                const auto [step, u, p, i, new_ret, ret] = stk.back(); stk.pop_back();
                if (step == 1) {
                    stk.emplace_back(4, u, -1, -1, nullptr, ret);
                    stk.emplace_back(2, u, p, 0, nullptr, ret);
                } else if (step == 2) {
                    if (i == size(adj[u])) {
                        continue;
                    }
                    const auto& v = adj[u][i];
                    stk.emplace_back(2, u, p, i + 1, new_ret, ret);
                    if (v == p) {
                        continue;
                    }
                    const auto& new_ret = make_shared<RET>(RET{cost[v]});
                    stk.emplace_back(3, -1, -1, -1, new_ret, ret);
                    stk.emplace_back(1, v, u, -1, nullptr, new_ret.get());
                } else if (step == 3) {
                    for (const auto& c : *new_ret) {
                        ret->emplace_back(c);
                    }
                    sort(begin(*ret), end(*ret));
                    if (size(*ret) > 5) {
                        ret->assign({(*ret)[0], (*ret)[1], (*ret)[size(*ret) - 3], (*ret)[size(*ret) - 2], (*ret)[size(*ret) - 1]});
                    }
                } else if (step == 4) {
                    result[u] = size(*ret) < 3 ? 1 : max({(*ret)[0] * (*ret)[1] * (*ret)[size(*ret) - 1], (*ret)[size(*ret) - 3] * (*ret)[size(*ret) - 2] * (*ret)[size(*ret) - 1], static_cast<int64_t>(0)});
                }
            }
            return result;
        };

        return iter_dfs();
    }

