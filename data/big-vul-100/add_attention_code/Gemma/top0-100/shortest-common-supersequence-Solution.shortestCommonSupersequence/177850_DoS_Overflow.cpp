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


    string shortestCommonSupersequence(string str1, string str2) {
        vector<vector<int>> dp(2, vector<int>(str2.size() + 1));
        vector<vector<tuple<int, int, char>>> bt(str1.size() + 1,
                                                 vector<tuple<int, int, char>>(str2.size() + 1));
        for (int i = 0; i < str1.length(); ++i) {
            bt[i + 1][0] = {i, 0, str1[i]};
        }
        for (int j = 0; j < str2.length(); ++j) {
            bt[0][j + 1] = {0, j, str2[j]};
        }
        for (int i = 0; i < str1.length(); ++i) {
            for (int j = 0; j < str2.length(); ++j) {
                if (dp[i % 2][j + 1] > dp[(i + 1) % 2][j]) {
                    dp[(i + 1) % 2][j + 1] = dp[i % 2][j + 1];
                    bt[i + 1][j + 1] = {i, j + 1, str1[i]};
                } else {
                    dp[(i + 1) % 2][j + 1] = dp[(i + 1) % 2][j];
                    bt[i + 1][j + 1] = {i + 1, j, str2[j]};
                }
                if (str1[i] != str2[j]) {
                    continue;
                }
                if (dp[i % 2][j] + 1 > dp[(i + 1) % 2][j + 1]) {
                    dp[(i + 1) % 2][j + 1] = dp[i % 2][j] + 1;
                    bt[i + 1][j + 1] = {i, j, str1[i]};
                }
            }
        }
        
        int i = str1.length(), j = str2.length();
        char c = 0;
        string result;
        while (i != 0 || j != 0) {
            tie(i, j, c) = bt[i][j];
            result.push_back(c);
        }
        reverse(result.begin(), result.end());
        return result;
    }


