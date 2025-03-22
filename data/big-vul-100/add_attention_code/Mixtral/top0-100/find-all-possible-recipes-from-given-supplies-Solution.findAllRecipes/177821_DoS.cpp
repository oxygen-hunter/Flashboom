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

    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_map<string, int> indegree;
        unordered_map<string, vector<string>> adj;
        for (int i = 0; i < size(recipes); ++i) {
            indegree[recipes[i]] = size(ingredients[i]);
            for (const auto& ing : ingredients[i]) {
                adj[ing].emplace_back(recipes[i]);
            }
        }
        vector<string> result;
        unordered_set<string> recipes_set(cbegin(recipes), cend(recipes));
        vector<string> q = supplies;
        while (!empty(q)) { 
            vector<string> new_q;
            for (const auto& u : q) {
                if (recipes_set.count(u)) {
                    result.emplace_back(u);
                }
                for (const auto& v : adj[u]) {
                    if (!--indegree[v]) {
                        new_q.emplace_back(v);
                    }
                }
            }
            q = move(new_q);
        }
        return result ;
    }

