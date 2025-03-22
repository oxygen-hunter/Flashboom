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


    int distinctSequences(int n) {
        static const int MOD = 1e9 + 7;
        if (n == 1) {
            return 6;
        }
        vector<vector<int>> dp(6, vector<int>(6));
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (i != j && gcd(i + 1, j + 1) == 1) {
                    dp[i][j] = 1;
                }
            }
        }
        for (int _ = 0; _ < n - 2; ++_) {
            vector<vector<int>> new_dp(6, vector<int>(6));
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 6; ++j) {
                    if (!dp[i][j]) {
                        continue;
                    }
                    for (int k = 0; k < 6; ++k) {
                        if (!dp[j][k]) {
                            continue;
                        }
                        if (k != i) {
                            new_dp[i][j] = (new_dp[i][j] + dp[j][k]) % MOD;
                        }
                    }
                }
            }
            dp = move(new_dp);
        }
        return accumulate(cbegin(dp), cend(dp), 0,
                          [&](int total, const auto& x) {
                              return (total + accumulate(cbegin(x), cend(x), 0,
                                                         [&](int total, int x) {
                                                             return (total + x) % MOD;
                                                         })) % MOD;
                          });
    }


