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

    int backtracking(const vector<string>& pieces, const vector<vector<int>>& positions, int i, vector<vector<int>> *lookup) {
        static const unordered_map<string, vector<pair<int, int>>> directions = {
            {"rook", {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}},
            {"bishop", {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}},
            {"queen", {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}}
        };
        static const int all_mask = (1 << 7) - 1;  // at most 7 seconds in 8x8 board

        if (i == size(pieces)) {
            return 1;
        }
        int result = 0;
        int r = positions[i][0] - 1, c = positions[i][1] - 1;
        int mask = all_mask;
        if (!((*lookup)[r][c] & mask)) {
            (*lookup)[r][c] += mask;  // stopped at (r, c)
            result += backtracking(pieces, positions, i + 1, lookup);
            (*lookup)[r][c] -= mask;
        }
        for (const auto& [dr, dc] : directions.at(pieces[i])) {
            int bit = 1, nr = r + dr, nc = c + dc;
            int mask = all_mask;  // (mask&bit == 1): (log2(bit)+1)th second is occupied
            for (; 0 <= nr && nr < 8 && 0 <= nc && nc < 8 && !((*lookup)[nr][nc] & bit); bit <<= 1, nr += dr, nc += dc) {
                (*lookup)[nr][nc] += bit;
                mask -= bit;
                if (!((*lookup)[nr][nc] & mask)) {  // stopped at (nr, nc)
                    (*lookup)[nr][nc] += mask;
                    result += backtracking(pieces, positions, i + 1, lookup);
                    (*lookup)[nr][nc] -= mask;
                }
            }
            while (bit >> 1) {
                bit >>= 1, nr -= dr, nc -= dc;
                (*lookup)[nr][nc] -= bit;
            }
        }
        return result;
    }

