datum_to_json(Datum val, bool is_null, StringInfo result,
			  JsonTypeCategory tcategory, Oid outfuncoid,
			  bool key_scalar)
{
	char	   *outputstr;
	text	   *jsontext;

	/* callers are expected to ensure that null keys are not passed in */
    char       *outputstr;
    text       *jsontext;
 
    /* callers are expected to ensure that null keys are not passed in */
    Assert(!(key_scalar && is_null));
 
	if (key_scalar &&
		(tcategory == JSONTYPE_ARRAY ||
		 tcategory == JSONTYPE_COMPOSITE ||
		 tcategory == JSONTYPE_JSON ||
		 tcategory == JSONTYPE_CAST))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
		 errmsg("key value must be scalar, not array, composite, or json")));

	switch (tcategory)
	{
		case JSONTYPE_ARRAY:
			array_to_json_internal(val, result, false);
			break;
		case JSONTYPE_COMPOSITE:
			composite_to_json(val, result, false);
			break;
		case JSONTYPE_BOOL:
			outputstr = DatumGetBool(val) ? "true" : "false";
			if (key_scalar)
				escape_json(result, outputstr);
			else
				appendStringInfoString(result, outputstr);
			break;
		case JSONTYPE_NUMERIC:
			outputstr = OidOutputFunctionCall(outfuncoid, val);

			/*
			 * Don't call escape_json for a non-key if it's a valid JSON
			 * number.
			 */
			if (!key_scalar && IsValidJsonNumber(outputstr, strlen(outputstr)))
				appendStringInfoString(result, outputstr);
			else
				escape_json(result, outputstr);
			pfree(outputstr);
			break;
		case JSONTYPE_DATE:
			{
				DateADT		date;
				struct pg_tm tm;
				char		buf[MAXDATELEN + 1];

				date = DatumGetDateADT(val);

				if (DATE_NOT_FINITE(date))
				{
					/* we have to format infinity ourselves */
					appendStringInfoString(result, DT_INFINITY);
				}
				else
				{
					j2date(date + POSTGRES_EPOCH_JDATE,
						   &(tm.tm_year), &(tm.tm_mon), &(tm.tm_mday));
					EncodeDateOnly(&tm, USE_XSD_DATES, buf);
					appendStringInfo(result, "\"%s\"", buf);
				}
			}
			break;
		case JSONTYPE_TIMESTAMP:
			{
				Timestamp	timestamp;
				struct pg_tm tm;
				fsec_t		fsec;
				char		buf[MAXDATELEN + 1];

				timestamp = DatumGetTimestamp(val);

				if (TIMESTAMP_NOT_FINITE(timestamp))
				{
					/* we have to format infinity ourselves */
					appendStringInfoString(result, DT_INFINITY);
				}
				else if (timestamp2tm(timestamp, NULL, &tm, &fsec, NULL, NULL) == 0)
				{
					EncodeDateTime(&tm, fsec, false, 0, NULL, USE_XSD_DATES, buf);
					appendStringInfo(result, "\"%s\"", buf);
				}
				else
					ereport(ERROR,
							(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
							 errmsg("timestamp out of range")));
			}
			break;
		case JSONTYPE_TIMESTAMPTZ:
			{
				TimestampTz timestamp;
				struct pg_tm tm;
				int			tz;
				fsec_t		fsec;
				const char *tzn = NULL;
				char		buf[MAXDATELEN + 1];

				timestamp = DatumGetTimestamp(val);

				if (TIMESTAMP_NOT_FINITE(timestamp))
				{
					/* we have to format infinity ourselves */
					appendStringInfoString(result, DT_INFINITY);
				}
				else if (timestamp2tm(timestamp, &tz, &tm, &fsec, &tzn, NULL) == 0)
				{
					EncodeDateTime(&tm, fsec, true, tz, tzn, USE_XSD_DATES, buf);
					appendStringInfo(result, "\"%s\"", buf);
				}
				else
					ereport(ERROR,
							(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
							 errmsg("timestamp out of range")));
			}
			break;
		case JSONTYPE_JSON:
			/* JSON and JSONB output will already be escaped */
			outputstr = OidOutputFunctionCall(outfuncoid, val);
			appendStringInfoString(result, outputstr);
			pfree(outputstr);
			break;
		case JSONTYPE_CAST:
			/* outfuncoid refers to a cast function, not an output function */
			jsontext = DatumGetTextP(OidFunctionCall1(outfuncoid, val));
			outputstr = text_to_cstring(jsontext);
			appendStringInfoString(result, outputstr);
			pfree(outputstr);
			pfree(jsontext);
			break;
		default:
			outputstr = OidOutputFunctionCall(outfuncoid, val);
			escape_json(result, outputstr);
			pfree(outputstr);
			break;
	}
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

