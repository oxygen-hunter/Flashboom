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

    vector<string> findHighAccessEmployees(vector<vector<string>>& access_times) {
        static const int LIMIT_COUNT = 2;
        static const int LIMIT_MINUTE = 60;
    
        const auto& to_minute = [](const auto& s) {
            return stoi(s.substr(0, 2)) * 60 + stoi(s.substr(2));
        };
    
        unordered_map<string, vector<int>> lookup;;
        for (const auto& x : access_times) {
            lookup[x[0]].emplace_back(to_minute(x[1]));
        }
        vector<string> result;
        for (auto& [x, ts] : lookup) {
            sort(begin(ts), end(ts));
            for (int i = 0; i + LIMIT_COUNT < size(ts); ++i) {
                if (!(ts[i] + LIMIT_MINUTE <= ts[i + LIMIT_COUNT])) {
                    result.emplace_back(x);
                    break;
                }
            } 
        }
        return result;
    }

