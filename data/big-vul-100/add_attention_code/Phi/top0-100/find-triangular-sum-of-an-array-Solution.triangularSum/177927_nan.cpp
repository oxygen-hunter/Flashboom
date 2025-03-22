PHP_FUNCTION(openssl_seal)
{
	zval *pubkeys, *pubkey, *sealdata, *ekeys, *iv = NULL;
	HashTable *pubkeysht;
	EVP_PKEY **pkeys;
	zend_resource ** key_resources;	/* so we know what to cleanup */
	int i, len1, len2, *eksl, nkeys, iv_len;
	unsigned char iv_buf[EVP_MAX_IV_LENGTH + 1], *buf = NULL, **eks;
	char * data;
	size_t data_len;
	char *method =NULL;
	size_t method_len = 0;
	const EVP_CIPHER *cipher;
	EVP_CIPHER_CTX *ctx;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sz/z/a/|sz/", &data, &data_len,
				&sealdata, &ekeys, &pubkeys, &method, &method_len, &iv) == FAILURE) {
		return;
	}
	pubkeysht = Z_ARRVAL_P(pubkeys);
	nkeys = pubkeysht ? zend_hash_num_elements(pubkeysht) : 0;
	if (!nkeys) {
		php_error_docref(NULL, E_WARNING, "Fourth argument to openssl_seal() must be a non-empty array");
		RETURN_FALSE;
	}

	PHP_OPENSSL_CHECK_SIZE_T_TO_INT(data_len, data);

	if (method) {
		cipher = EVP_get_cipherbyname(method);
		if (!cipher) {
			php_error_docref(NULL, E_WARNING, "Unknown signature algorithm.");
			RETURN_FALSE;
		}
	} else {
		cipher = EVP_rc4();
	}

	iv_len = EVP_CIPHER_iv_length(cipher);
	if (!iv && iv_len > 0) {
		php_error_docref(NULL, E_WARNING,
				"Cipher algorithm requires an IV to be supplied as a sixth parameter");
		RETURN_FALSE;
	}

	pkeys = safe_emalloc(nkeys, sizeof(*pkeys), 0);
	eksl = safe_emalloc(nkeys, sizeof(*eksl), 0);
	eks = safe_emalloc(nkeys, sizeof(*eks), 0);
	memset(eks, 0, sizeof(*eks) * nkeys);
	key_resources = safe_emalloc(nkeys, sizeof(zend_resource*), 0);
	memset(key_resources, 0, sizeof(zend_resource*) * nkeys);
	memset(pkeys, 0, sizeof(*pkeys) * nkeys);

	/* get the public keys we are using to seal this data */
	i = 0;
	ZEND_HASH_FOREACH_VAL(pubkeysht, pubkey) {
		pkeys[i] = php_openssl_evp_from_zval(pubkey, 1, NULL, 0, 0, &key_resources[i]);
		if (pkeys[i] == NULL) {
			php_error_docref(NULL, E_WARNING, "not a public key (%dth member of pubkeys)", i+1);
			RETVAL_FALSE;
			goto clean_exit;
		}
		eks[i] = emalloc(EVP_PKEY_size(pkeys[i]) + 1);
		i++;
	} ZEND_HASH_FOREACH_END();

	ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL || !EVP_EncryptInit(ctx,cipher,NULL,NULL)) {
		EVP_CIPHER_CTX_free(ctx);
		RETVAL_FALSE;
		goto clean_exit;
	}

	/* allocate one byte extra to make room for \0 */
        buf = emalloc(data_len + EVP_CIPHER_CTX_block_size(ctx));
        EVP_CIPHER_CTX_cleanup(ctx);
 
       if (!EVP_SealInit(ctx, cipher, eks, eksl, &iv_buf[0], pkeys, nkeys) ||
                        !EVP_SealUpdate(ctx, buf, &len1, (unsigned char *)data, (int)data_len) ||
                        !EVP_SealFinal(ctx, buf + len1, &len2)) {
                RETVAL_FALSE;
		efree(buf);
		EVP_CIPHER_CTX_free(ctx);
		goto clean_exit;
	}

	if (len1 + len2 > 0) {
		zval_dtor(sealdata);
		ZVAL_NEW_STR(sealdata, zend_string_init((char*)buf, len1 + len2, 0));
		efree(buf);

		zval_dtor(ekeys);
		array_init(ekeys);
		for (i=0; i<nkeys; i++) {
			eks[i][eksl[i]] = '\0';
			add_next_index_stringl(ekeys, (const char*)eks[i], eksl[i]);
			efree(eks[i]);
			eks[i] = NULL;
		}

		if (iv) {
			zval_dtor(iv);
			iv_buf[iv_len] = '\0';
			ZVAL_NEW_STR(iv, zend_string_init((char*)iv_buf, iv_len, 0));
		}
	} else {
		efree(buf);
	}
	RETVAL_LONG(len1 + len2);
	EVP_CIPHER_CTX_free(ctx);

clean_exit:
	for (i=0; i<nkeys; i++) {
		if (key_resources[i] == NULL && pkeys[i] != NULL) {
			EVP_PKEY_free(pkeys[i]);
		}
		if (eks[i]) {
			efree(eks[i]);
		}
	}
	efree(eks);
	efree(eksl);
	efree(pkeys);
	efree(key_resources);
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

