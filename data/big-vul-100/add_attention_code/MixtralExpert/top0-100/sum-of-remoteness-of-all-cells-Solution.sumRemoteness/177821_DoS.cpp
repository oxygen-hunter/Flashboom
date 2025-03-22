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


    long long sumRemoteness(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> DIRECTIONS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        const auto& bfs = [&](int i, int j) {
            int64_t total = grid[i][j];
            int cnt = 1;
            grid[i][j] = -1;
            vector<pair<int64_t, int>> q = {{i, j}};
            while (!empty(q)) {
                vector<pair<int64_t, int>> new_q;
                for (const auto& [i, j] : q) {
                    for (const auto& [di, dj] : DIRECTIONS) {
                        int ni = i + di, nj = j + dj;
                        if (!(0 <= ni && ni < size(grid) &&
                              0 <= nj && nj < size(grid[0]) &&
                              grid[ni][nj] != -1)) {
                            continue;
                        }
                        total += grid[ni][nj];
                        ++cnt;
                        grid[ni][nj] = -1;
                        new_q.emplace_back(ni, nj);
                    }
                }
                q = move(new_q);
            }
            return pair(total, cnt);
        };
    
        vector<pair<int64_t, int>> groups;
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                if (grid[i][j] == -1) {
                    continue;
                }
                groups.emplace_back(bfs(i, j));
            }
        }
        int64_t total = 0;
        for (const auto& [t, _] : groups) {
            total += t;
        }
        int64_t result = 0;
        for (const auto& [t, c] : groups) {
            result += (total - t) * c;
        }
        return result;
    }


