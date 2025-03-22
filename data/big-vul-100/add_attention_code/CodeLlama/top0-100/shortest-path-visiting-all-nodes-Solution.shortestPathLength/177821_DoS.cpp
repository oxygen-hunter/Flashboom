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


    int shortestPathLength(vector<vector<int>>& graph) {
        static const auto& INF = numeric_limits<int>::max();
        vector<vector<int>> dp(1 << graph.size(),
                               vector<int>(graph.size(), INF));
        queue<pair<int, int>> q;
        for (int i = 0; i < graph.size(); ++i) {
            dp[1 << i][i] = 0;
            q.emplace(1 << i, i);
        }
        while (!q.empty()) {
            int state, node;
            tie(state, node) = q.front(); q.pop();
            auto steps = dp[state][node];
            for (const auto& nei : graph[node]) {
                auto new_state = state | (1 << nei);								
                if (dp[new_state][nei] == INF) {
                    dp[new_state][nei] = steps + 1;
                    q.emplace(new_state, nei);
                }
            }
        }
        return *min_element(dp.back().cbegin(), dp.back().cend());
    }


