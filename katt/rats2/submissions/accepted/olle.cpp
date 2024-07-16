using namespace std;
#include <bits/stdc++.h>

#define rep(i,a,b) for(int i = a; i < b; i++)
#define pb push_back

int n, k;
vector<int> rats, targets, non_targets;
set<int> rats_set, targets_set, non_targets_set;
vector<set<int>> g;
vector<bool> finished;
int query_count = 0;
unsigned seed;

bool DEBUG = false;
ofstream myfile;


void query(vector<int> arr) {
    if (arr.size() == 0) return;
    query_count++;
    sort(arr.begin(), arr.end());
    cout << arr.size() << " ";
    for (auto x : arr) cout << x + 1 << " ";
    cout << endl;
    
    if (DEBUG) myfile << " < " << arr.size() << " ";
    for (auto x : arr) if (DEBUG) myfile << x + 1 << " ";
    if (DEBUG) myfile << endl;

    rep(i,0,k) cin >> rats[i];

    if (DEBUG) myfile << " > ";
    rep(i,0,k) if (DEBUG) myfile << rats[i] << " ";
    if (DEBUG) myfile << endl;
    rep(i,0,k) rats[i]--;
    rats_set.clear();
    rep(i,0,k) rats_set.insert(rats[i]);
}

void query(set<int> s) {
    vector<int> arr;
    for (auto x : s) arr.pb(x);
    query(arr);
}

void query_all_except(set<int> s) {
    vector<int> arr;
    rep(i,0,n) if (s.find(i) == s.end()) arr.pb(i);
    query(arr);
}

void query_all_except(int x) {
    vector<int> arr;
    rep(i,0,n) if (i != x) arr.pb(i);
    query(arr);
}

void query(int x) {
    vector<int> arr = {x};
    query(arr);
}

void get_all_neighbors(int node) {
    assert(rats_set.find(node) != rats_set.end() && (!finished[node]));

    while (true) {
        auto node_and_nei = [&]() {
            set<int> s = {node};
            for (auto x : g[node]) if (rats_set.find(x) == rats_set.end()) s.insert(x);
            return s;
        };

        while (rats_set.find(node) != rats_set.end()) {
            set<int> old_rats = rats_set;
            query(node_and_nei());
            if (rats_set == old_rats) while (rats_set.find(node) != rats_set.end()) query(node);
        }

        set<int> old = rats_set;

        set<int> query_now = {node};
        for (auto x : g[node]) if (rats_set.find(x) != rats_set.end()) query_now.insert(x);

        query_all_except(query_now);

        int diff = -1;
        for (auto x : old) if (rats_set.find(x) == rats_set.end()) diff = x;
        if (diff == -1 || g[node].find(diff) != g[node].end()) break;
        g[node].insert(diff);
    }

    finished[node] = true;
}

void get_graph() {
    auto get_next_node = [&]() {
        for (auto x : rats_set) if (!finished[x]) return x;
        return -1;
    };
    
    int nodes_left = n;
    
    while (nodes_left) {
        int node = get_next_node();
        if (node == -1) {
            set<int> Query;
            rep(i,0,n) if (finished[i]) Query.insert(i);
            query(Query);
        }

        set<int> next_query;
        set<int> empty;
        vector<set<int>> history_rats = {rats_set};

        auto all_same = [&](set<int> & old_rats) {
            if (old_rats.size() != rats_set.size()) return false;
            for (auto x : rats) if (old_rats.find(x) == old_rats.end()) return false;
            return true;
        };

        while (node == -1) {
            for (auto x : rats_set) next_query.insert(x);
            query(next_query);

            if (all_same(history_rats[history_rats.size() - 1])) {
                assert(history_rats.size() > 1);
                auto to = history_rats.back();
                while (all_same(to)) {
                    history_rats.pop_back();
                    to = history_rats.back();
                }
                query_all_except(to);
            }
            else {
                history_rats.push_back(rats_set);
            }

            node = get_next_node();
        }

        get_all_neighbors(node);
        nodes_left--;
    }

    
    // fix leaves
    vector<set<int>> new_g(n);
    rep(i,0,n) for (auto j : g[i]) {
        if (g[j].find(i) != g[j].end()) new_g[i].insert(j);
    }

    g = new_g;

    set<pair<int,int>> edges, edges_to_remove;
    rep(i,0,n) for (auto j : g[i]) edges.insert({i, j});

    for (auto [a, b] : edges) rep(c,0,min(a, b)) {
        if (a > b) continue;
        if (edges.find({a, c}) != edges.end() && edges.find({b, c}) != edges.end()) {
            edges_to_remove.insert({a, b});
        }
    }

    for (auto [a, b] : edges_to_remove) {
        g[a].erase(b);
        g[b].erase(a);
    }
}

set<int> dfs_component(int x, int p, set<int> & nodes) {
    set<int> res = {x};
    for (auto y : g[x]) if (nodes.find(y) != nodes.end() && y != p) {
        set<int> got = dfs_component(y, x, nodes);
        if (got.size() > res.size()) swap(got, res);
        for (auto _ : got) res.insert(_);
    }
    return res;
}

set<int> get_rats(set<int> & nodes, set<int> current_rats, set<int> & query, set<int> constant_queries) {
    map<int, bool> occupied;
    for (auto x : nodes) occupied[x] = false;
    for (auto x : current_rats) occupied[x] = true;

    auto getScore = [&]() -> map<int,int> {
        map<int,int> score;
        queue<int> q;
        for (auto x : query) {
            score[x] = 0;
            q.push(x);
        }
        for (auto x : constant_queries) {
            score[x] = 0;
            q.push(x);
        }
        while (!q.empty()) {
            auto x = q.front(); q.pop();
            for (auto y : g[x]) if (nodes.find(y) != nodes.end() && score.find(y) == score.end()) {
                score[y] = score[x] + 1;
                q.push(y);
            }
        }
        return score;
    };

    map<int,int> score = getScore();
    set<int> new_rats;
    for (auto r : current_rats) {
        int best = r;
        int best_score = score[r];
        for (auto x : g[r]) if (nodes.find(x) != nodes.end() && (!occupied[x])) {
            if ((score[x] > best_score) || (score[x] == best_score && x < best && best != r)) {
                best = x;
                best_score = score[x];
            }
        }
        occupied[r] = false;
        occupied[best] = true;
    }
    for (auto [x, status] : occupied) {
        if (status) new_rats.insert(x);
    }

    return new_rats;
} 

vector<set<int>> get_queries(set<int> nodes, set<int> current_rats, set<int> constant_queries) {
    if (DEBUG) myfile << "calling get_queries" << endl;
    vector<set<int>> queries;
    vector<int> nodes_list;
    for (auto x : nodes) {
        nodes_list.pb(x);
        for (auto nei : g[x]) if (nodes.find(nei) != nodes.end()) nodes_list.pb(nei);
    }

    // could use better heuristic to find center -- maybe centroid
    shuffle(nodes_list.begin(), nodes_list.end(), default_random_engine(seed));
    int center = -1; 
    for (auto x : nodes_list) if (targets_set.find(x) == targets_set.end()) {
        center = x;
        break;
    }
    if (center == -1) return queries;

    vector<set<int>> components;
    map<int,int> index2node;
    map<int,int> node2index;
    int index = 0;
    for (auto x : g[center]) if (nodes.find(x) != nodes.end()) {
        components.pb(dfs_component(x, center, nodes));
        index2node[index] = x;
        node2index[x] = index;
        index++;
    }

    int component_count = components.size();
    if (DEBUG) myfile << "component_count: " << component_count << endl;
    vector<int> rat_count(component_count,0), target_count(component_count,0);

    auto update_rat_count = [&]() {
        rat_count.assign(component_count, 0);
        target_count.assign(component_count, 0);
        rep(i,0,component_count) {
            for (auto x : components[i]) {
                if (current_rats.find(x) != current_rats.end()) rat_count[i]++;
                if (targets_set.find(x) != targets_set.end()) target_count[i]++;
            }
        }
        rep(i,0,component_count) if (DEBUG) myfile << "component " << i << " has " << rat_count[i] << " rats and " << target_count[i] << " targets." << endl;
    };
    update_rat_count();

    auto propagate_away_from_center = [&](int NODE) {
        set<int> Query = nodes;
        if (current_rats.find(NODE) == current_rats.end()) {
            Query.erase(NODE);
            for (int nei : g[NODE]) if (nodes.find(nei) != nodes.end()) if (nei != center) if (current_rats.find(nei) != current_rats.end()) Query.erase(nei);
            queries.pb(Query);
            current_rats = get_rats(nodes, current_rats, Query, constant_queries);
            return;
        }

        queue<pair<int,int>> q;
        q.push({NODE, center});
        set<int> will_go_to;

        while (!q.empty()) {
            auto [node, parent] = q.front(); q.pop();
            if (current_rats.find(node) != current_rats.end()) {
                for (auto nei : g[node]) if (nodes.find(nei) != nodes.end()) if (nei != parent) if (current_rats.find(nei) == current_rats.end() && will_go_to.find(nei) == will_go_to.end()) {
                    will_go_to.insert(nei);
                    Query.erase(nei);
                    break;
                }
            }
            if (will_go_to.find(node) != will_go_to.end()) {
                for (auto nei : g[node]) if (nodes.find(nei) != nodes.end()) if (nei != parent) {
                    if (current_rats.find(nei) != current_rats.end()) Query.erase(nei);
                }
            }


            for (auto nei : g[node]) if (nodes.find(nei) != nodes.end()) if (nei != parent) {
                q.push({nei, node});
            }
        }

        queries.pb(Query);
        current_rats = get_rats(nodes, current_rats, Query, constant_queries);
    };

    while (true) {
        if (current_rats.find(center) != current_rats.end()) {
            int target_node = -1;
            rep(i,0,component_count) if (rat_count[i] < target_count[i]) target_node = index2node[i];
            propagate_away_from_center(target_node);
            
            update_rat_count();
        }
        else {
            set<int> Query = nodes;

            auto lure_rats_to_center = [&](int index) {
                set<int> component = components[index];
                int root = index2node[index];

                if (DEBUG) myfile << "Luring to " << center +1 << " from " << root+1 << endl;
                for (auto K : component) {
                    if (current_rats.find(K) != current_rats.end()) if (DEBUG) myfile << "[";
                    if (DEBUG) myfile << K+1 ;
                    if (current_rats.find(K) != current_rats.end()) myfile<< "]";
                    if (DEBUG) myfile << " ";

                }
                if (DEBUG) myfile << "!" << endl;

                map<int, int> came_from;
                for (auto node : component) came_from[node] = -1;
                came_from[root] = center;

                if (current_rats.find(root) != current_rats.end()) {
                    Query.erase(center);
                    for (auto nei : g[center]) if (nodes.find(nei) != nodes.end() && current_rats.find(nei) != current_rats.end() && nei != root)
                        Query.erase(nei);
                    return;
                }

                queue<int> q;
                q.push(root);
                
                set<int> nodes_of_interest;
                set<int> rats_of_interest;
                
                while (!q.empty()) {
                    auto x = q.front(); q.pop();
                    bool interesting = false;
                    for (auto nei : g[x]) if (rats_of_interest.find(nei) != rats_of_interest.end() || nodes_of_interest.find(nei) != nodes_of_interest.end()) interesting = true;
                    for (auto nei : g[x]) {
                        if (component.find(nei) == component.end()) continue;
                        if (came_from[nei] != -1) continue;

                        came_from[nei] = x;

                        if (!interesting) if (current_rats.find(nei) != current_rats.end() && current_rats.find(x) == current_rats.end() && rats_of_interest.find(nei) == rats_of_interest.end()) {
                            interesting = true;
                            rats_of_interest.insert(nei);
                            nodes_of_interest.insert(x);
                        }

                        q.push(nei);
                    }
                }
                for (auto node : nodes_of_interest) Query.erase(node);
                for (auto node : component) if (current_rats.find(node) != current_rats.end() && rats_of_interest.find(node) == rats_of_interest.end()) Query.erase(node);
            };

            bool all_done = true;
            rep(i,0,component_count) {
                if (rat_count[i] > target_count[i]) {
                    lure_rats_to_center(i);
                    all_done = false;
                    break;
                }
                if (rat_count[i] != target_count[i]) all_done = false;
            }

            if (all_done) {
                constant_queries.insert(center);

                vector<vector<set<int>>> all_comp_queries;

                int M = queries.size();
                int m = 0;
                for (auto comp : components) {
                    set<int> partial_rats;
                    for (auto x : current_rats) if (comp.find(x) != comp.end()) partial_rats.insert(x);
                    if (DEBUG) myfile << "getting component with element " << (*comp.begin())+1 << " and size " << comp.size() << endl;
                    vector<set<int>> comp_queries = get_queries(comp, partial_rats, constant_queries);
                    all_comp_queries.pb(comp_queries);
                    if (DEBUG) myfile << "got component with element " << (*comp.begin())+1 << " and size " << comp.size() << endl;

                    
                    m = max(m, (int)comp_queries.size());
                }
                if (DEBUG) myfile << "m = " << m << endl;
                for (auto x : all_comp_queries) if (DEBUG) myfile << x.size() << " ";
                if (DEBUG) myfile << " sizes " << endl;

                rep(i,0,component_count) {
                    while (all_comp_queries[i].size() < m) all_comp_queries[i].pb(components[i]);
                }

                rep(i,0,m) {
                    set<int> Q;
                    rep(j,0,component_count) {
                        if (Q.size() < all_comp_queries[j][i].size()) swap(Q,all_comp_queries[j][i]);
                        for (auto x : all_comp_queries[j][i]) Q.insert(x);
                    }
                    for (auto x : constant_queries) Q.insert(x);
                    queries.pb(Q);
                }


                rep(i,M,queries.size()) current_rats = get_rats(nodes, current_rats, queries[i], constant_queries);

                if (DEBUG) myfile << "Finised with component "; for (auto node : nodes) if (DEBUG) myfile << node+1 << " "; if (DEBUG) myfile << endl;
                if (DEBUG) myfile << "With rats "; for (auto node : current_rats) if (DEBUG) myfile << node+1 << " "; if (DEBUG) myfile << endl;
                return queries;
            }

            if (DEBUG) myfile << "querying ";
            for (auto x : Query) if (DEBUG) myfile << x+1 << " " ;
            if (DEBUG) myfile << endl;
            queries.pb(Query);
            current_rats = get_rats(nodes, current_rats, Query, constant_queries);
        }
    }

}

int main() {
    if (DEBUG) myfile.open ("log.txt");

    seed = 6215;//std::chrono::system_clock::now().time_since_epoch().count();
    cin >> n >> k;
    rats.resize(k);
    targets.resize(k);
    g.resize(n);
    finished.assign(n, false);
    rep(i,0,k) cin >> rats[i];
    rep(i,0,k) rats[i]--;
    rep(i,0,k) rats_set.insert(rats[i]);
    rep(i,0,k) cin >> targets[i];
    rep(i,0,k) targets[i]--;
    rep(i,0,k) targets_set.insert(targets[i]);
    rep(i,0,n) if (targets_set.find(i) == targets_set.end()) non_targets.pb(i);
    for (auto x : non_targets) non_targets_set.insert(x);

    get_graph();

    set<int> nodes;
    rep(i,0,n) nodes.insert(i);
    set<int> current_rats = rats_set;
    set<int> constant_queries;
    vector<set<int>> queries = get_queries(nodes, current_rats, constant_queries);

    for (auto Q : queries) query(Q);

    cout << "activate!\n";
    if (DEBUG) myfile.close();

    return 0;
}