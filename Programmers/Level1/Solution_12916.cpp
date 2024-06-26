#include "Solution_12916.h"

Solution_12916::Solution_12916()
{
}

int Solution_12916::solution(vector<string> friends, vector<string> gifts)
{
    int answer = 0;
    map<string, int> gift_points;
    map<string, int> next_month;
    map<string, map<string, int>> give_takes;
    map<string, int> temp;

    vector<pair<string, string>> pair_friends;
    for (int i = 0; i < friends.size(); ++i)
        for (int j = i + 1; j < friends.size(); ++j)
            if (i != j)
                pair_friends.push_back(make_pair(friends[i], friends[j]));

    for (auto e : friends)
        temp[e];
    for (auto e : friends)
        give_takes[e].insert(temp.begin(), temp.end());

    for_each(gifts.begin(), gifts.end(), [&](string str) {
        string_view sv(str);
        size_t pos = 0;
        string sender;
        string receiver;

        while (pos != string::npos)
        {
            size_t next_pos = sv.find(' ', pos);
            if (next_pos == string::npos)
            {
                receiver = sv.substr(pos);
                gift_points[receiver]--;
                break;
            }
            else
            {
                sender = sv.substr(pos, next_pos - pos);
                gift_points[sender]++;
            }
            pos = next_pos + 1;
        }
        give_takes[sender][receiver]++;
        });

    vector<pair<string, string>> equals_count;
    for_each(give_takes.begin(), give_takes.end(), [&](pair<string, map<string, int>> elements) {
        string itsme = elements.first;
        string receiver_name = "";
        int send_count = 0;
        int recv_count = 0;
        for (auto receiver : elements.second)
        {
            if ((receiver.first != elements.first) && receiver.second > 0)
            {
                send_count = receiver.second;

                auto it = give_takes.find(receiver.first);
                receiver_name = it->first;
                pair_friends.erase(remove_if(pair_friends.begin(), pair_friends.end(), [&](pair<string, string> e) {
                    return (e.first == itsme && e.second == receiver_name) || (e.first == receiver_name && e.second == itsme);
                    }), pair_friends.end());

                for (auto sender_to_me : it->second)
                {
                    if (sender_to_me.first == itsme)
                    {
                        recv_count = sender_to_me.second;
                        if (itsme == "alessandro" || receiver_name == "alessandro")
                        {
                            int a = 0;
                        }
                        if (((send_count == recv_count)) && (gift_points[itsme] != gift_points[receiver_name]))
                        {
                            auto it = find_if(equals_count.begin(), equals_count.end(), [&](pair<string, string> e) {
                                return (e.first == itsme && e.second == receiver_name) || (e.first == receiver_name && e.second == itsme);
                                });
                            if (it != equals_count.end())
                                continue;
                            else
                                equals_count.push_back(make_pair(itsme, receiver_name));
                            gift_points[itsme] > gift_points[receiver_name] ? next_month[itsme]++ : next_month[receiver_name]++;
                        }
                        next_month[itsme] += (send_count > recv_count ? 1 : 0);
                    }
                }
            }
        }
        });

    for_each(pair_friends.begin(), pair_friends.end(), [&](pair<string, string> e) {
        if (gift_points[e.first] != gift_points[e.second])
            gift_points[e.first] > gift_points[e.second] ? next_month[e.first]++ : next_month[e.second]++;
        });
    auto max_val = max_element(next_month.begin(), next_month.end(), [](pair<string, int> p1, pair<string, int> p2) {
        return p1.second < p2.second;
        });
    return answer = max_val->second;
}