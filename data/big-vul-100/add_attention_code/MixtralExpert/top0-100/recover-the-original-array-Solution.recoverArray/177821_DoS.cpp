 QString IRCView::openTags(TextHtmlData* data, int from)
 {
     QString ret, tag;
    int i = from;
     for ( ;  i < data->openHtmlTags.count(); ++i)
     {
         tag = data->openHtmlTags.at(i);
            if (data->reverse)
            {
                ret += fontColorOpenTag(Preferences::self()->color(Preferences::TextViewBackground).name());
            }
            else
            {
                ret += fontColorOpenTag(data->lastFgColor);
            }
        }
        else if (tag == QLatin1String("span"))
        {
            if (data->reverse)
            {
                ret += spanColorOpenTag(data->defaultColor);
            }
            else
            {
                ret += spanColorOpenTag(data->lastBgColor);
            }
        }
        else
        {
            ret += QLatin1Char('<') + tag + QLatin1Char('>');
        }
    }


    vector<int> recoverArray(vector<int>& nums) {    
        auto check = [&nums](int k, unordered_map<int, int> cnt, vector<int> *result) {
            for (const auto& x : nums) {
                if (cnt[x] == 0) {
                    continue;
                }
                if (cnt[x + 2 * k] == 0) {
                    return false;
                }
                --cnt[x];
                --cnt[x + 2 * k];
                result->emplace_back(x + k);
            }
            return true;
        };
        sort(begin(nums), end(nums));
        unordered_map<int, int> cnt;
        for (const auto& x : nums) {
            ++cnt[x];
        }
        for (int i = 1; i <= size(nums) / 2; ++i) {
            int k = nums[i] - nums[0];
            if (k == 0 || k % 2) {
                continue;
            }
            k /= 2;
            vector<int> result;
            if (check(k, cnt, &result)) {
                return result;
            }
        }
        return {};
    }


