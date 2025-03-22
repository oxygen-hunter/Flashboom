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

    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        using P = pair<int, int>;
        unordered_map<int, vector<P>> adj;
        for (const auto& edge : edges) {
            int u, v, w;
            tie(u, v, w) = make_tuple(edge[0], edge[1],edge[2]);
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        
        unordered_map<int, int> best;
        best[0] = 0;
        using T = tuple<int, int, int>;
        priority_queue<T, vector<T>, greater<T>> min_heap;
        min_heap.emplace(passingFees[0], 0, 0);
        while (!empty(min_heap)) {
            const auto [result, u, w] = min_heap.top(); min_heap.pop();
            if (w > maxTime) {  // state with best[u] < w can't be filtered, which may have less cost
                continue;
            }
            if (u == size(passingFees) - 1) {
                return result;
            }
            for (const auto& [v, nw] : adj[u]) {
                if (!best.count(v) || w + nw < best[v]) {  // from less cost to more cost, only need to check state with less time
                    best[v] = w + nw;
                    min_heap.emplace(result + passingFees[v], v, w + nw);
                }
            }
        }
        return -1;
    }

