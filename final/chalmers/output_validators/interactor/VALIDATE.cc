#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

const int MAX_APP = 500;
const int MAX_WALK = 5000;
int N;

struct Room {
    int levels;
    vector<vector<bool>> room;
    vector<vector<int>> room_prefix;

    Room(vector<vector<int>> &r) {
        levels = r.size();
        room.resize(levels);
        room_prefix.resize(levels);
        rep(level,0,levels) {
            room[level].resize(1<<level);
            room_prefix[level].resize(1<<level);
            room[level][0] = (r[level][0] == 1);
            room_prefix[level][0] = r[level][0];
            rep(R,1,1<<level) {
                room[level][R] = (r[level][R] == 1);
                room_prefix[level][R] = room_prefix[level][R-1] + r[level][R];
            }
        }
    }

    bool can_go(int level, int a, int b) {
        if (b < a) swap(a, b);
        return (room_prefix[level][b] - room_prefix[level][a] == b - a);
    }

    int distance(int level1, int offset1, int level2, int offset2) {
        int dist = 0;
        if (level1 > level2) {
            swap(level1, level2);
            swap(offset1, offset2);
        }
        int iter_counts = 0;
        while (level1 < level2) {
            level2--;
            dist++;
            offset2 /= 2;
            iter_counts++;
            if (iter_counts > 1000) judge_error("inf loop\n");
        }
        iter_counts = 0;
        while(!can_go(level1, offset1, offset2)) {
            iter_counts++;
            level1--;
            dist += 2;
            offset1 /= 2;
            offset2 /= 2;
            if (iter_counts > 1000) judge_error("inf loop\n");
        }
        dist += abs(offset2 - offset1);
        return dist;
    }
};

struct Position {
    int true_level;
    int relative_level; // level within copy structure
    int offset;
    Position *up_copy_position = NULL;
    Room &room;

    Position(int true_level, int relative_level, int offset, Room &room) 
        :true_level(true_level), relative_level(relative_level), offset(offset), room(room) {}

    bool can_go_left() {
        if (offset == 0) return false;
        return (room.room[relative_level][offset - 1]);
    }

    void go_left() {
        offset--;
    }

    bool can_go_right() {
        if (offset == (1<<relative_level)-1) return false;
        return (room.room[relative_level][offset + 1]);
    }

    void go_right() {
        offset++;
    }

    bool can_go_up() {
        if (true_level == 0) return false;
        return true;
    }

    void go_up() {
        judge_message("going up from: %d %d %d\n", true_level, relative_level, offset);

        true_level--;
        if (relative_level == 0) {
            judge_message("going up to pointer, level is %d\n", true_level);
            if (up_copy_position == NULL) {
                judge_error("no up copy pointer\n");
            }
            Position *new_ptr = up_copy_position;
            true_level = new_ptr->true_level;
            relative_level = new_ptr->relative_level;
            offset = new_ptr->offset;
            up_copy_position = new_ptr->up_copy_position;
            delete new_ptr;
        }
        else {
            relative_level--;
            offset /= 2;
        }
    }

    bool can_go_down_left() {
        if (true_level == N - 1) return false;
        if (relative_level == (room.room.size()-1)) return true;
        return room.room[relative_level+1][2*offset];
    }

    void go_down_left() {
        if (relative_level != (room.room.size()-1)) {
            relative_level++;
            true_level++;
            offset *= 2;
        }
        else {
            Position* old_pos = new Position(true_level, relative_level, offset, room);
            old_pos->up_copy_position = up_copy_position;
            up_copy_position = old_pos;
            true_level++;
            relative_level = 0;
            offset = 0;
        }
    }

    bool can_go_down_right() {
        if (true_level == N - 1) return false;
        if (relative_level == (room.room.size()-1)) return false;
        return room.room[relative_level+1][2*offset+1] == 1;
    }

    void go_down_right() {
        if (relative_level != (room.room.size()-1)) {
            relative_level++;
            true_level++;
            offset = 2 * offset + 1;
        }
        else {
            judge_error("invalid move\n");
        }
    }

    string info() {
        string _ = "00000";
        if (can_go_up()) _[0] = '1';
        if (can_go_right()) _[1] = '1';
        if (can_go_down_right()) _[2] = '1';
        if (can_go_down_left()) _[3] = '1';
        if (can_go_left()) _[4] = '1';
        return _;
    }
};

void run_copy_down() {
    int c, n;
    judge_in >> c >> n;
    N = n;
    vector<vector<int>> room(c);
    rep(r,0,c) {
        room[r].resize(1<<r);
        rep(i,0,1<<r) {
            if (!(judge_in >> room[r][i])) judge_error("Did not read full room setup\n");
            if (!(room[r][i] == 0 || room[r][i] == 1)) judge_error("Room config not 0 or 1. (room[%d][%d] = %d)\n", r, i, room[r][i]);
        }
    }

    if (room[0][0] == 0) {
        judge_error("No room at first level\n");
    }

    rep(r,1,c) {
        rep(i,0,1<<r) if (room[r][i] == 1 && room[r-1][i/2] == 0) judge_error("No room above room[%d][%d]\n", i, r);
    }
    int A, B;
    judge_in >> A;
    if (A < 0 || A > n) judge_error("Impossible path length for start path (%d)\n", A);
    vector<int> path_start(A);
    rep(i,0,A) judge_in >> path_start[i];
    rep(i,0,A) if (!(path_start[i] == 0 || path_start[i] == 1)) judge_error("Path to start has invalid values (%d)\n", path_start[i]);
    judge_in >> B;
    if (B < 0 || B > n) judge_error("Impossible path length for start path (%d)\n", B);
    vector<int> path_goal(B);
    rep(i,0,B) judge_in >> path_goal[i];
    rep(i,0,B) if (!(path_goal[i] == 0 || path_goal[i] == 1)) judge_error("Path to start has invalid values (%d)\n", path_start[i]);

    Room r(room);

    Position cur = Position(0, 0, 0, r),
             goal = Position(0, 0, 0, r);

    int lca_level_cur = 0, lca_offset_cur = 0, lca_level_goal = 0, lca_offset_goal = 0;
    bool lca_goal_found = false;

    rep(i,0,A) {
        if (path_start[i] == 0) {
            if (!cur.can_go_down_left()) judge_error("Path to start makes illegal step\n");
            cur.go_down_left();
        }
        else {
            if (!cur.can_go_down_right()) judge_error("Path to start makes illegal step\n");
            cur.go_down_right();
        }

        if (i < B && (!lca_goal_found)) {
            if (path_goal[i] == 0) {
                if (!goal.can_go_down_left()) judge_error("Path to start makes illegal step\n");
                goal.go_down_left();
            }
            else {
                if (!goal.can_go_down_right()) judge_error("Path to start makes illegal step\n");
                goal.go_down_right();
            }

            if (r.can_go(cur.relative_level, cur.offset, goal.offset)) {
                lca_level_cur = cur.true_level;
                lca_offset_cur = cur.offset;
                lca_level_goal = goal.true_level;
                lca_offset_goal = goal.offset;

                if (cur.relative_level == r.room.size() - 1 && lca_offset_cur != lca_offset_goal) {
                    lca_goal_found = true;
                }
            }
            else {
                lca_goal_found = true;
                goal.go_up();
            }
        }
    }
    
    auto get_distance = [&]() {
        return (cur.true_level - lca_level_cur) + (B - lca_level_goal) + abs(lca_offset_cur - lca_offset_goal);
    };

    /////////// INTERACTION STARTS HERE /////////////
    //FILE *LOG = fopen("validator_log.txt", "w");

    int app_count = 0, walk_count = 0;
    cout << cur.info() << endl;

    int x = 0;

    while (true) {
        //fclose(LOG);
        //LOG = fopen("validator_log.txt", "a");
        
        x++;
        if(x > 10000) judge_error("too many x\n");
        judge_message("cur pos: %d %d %d\n", cur.true_level, cur.relative_level, cur.offset);
        judge_message("goal pos: %d %d %d\n", goal.true_level, goal.relative_level, goal.offset);
        judge_message("lca info: %d %d %d %d\n", lca_level_cur, lca_offset_cur, lca_level_goal, lca_offset_goal);

        string command;

        if (!(author_out >> command)) wrong_answer("Expected more commands\n");
        if (command == "app") {
            judge_message("app\n");
            app_count++;
            if (app_count > MAX_APP) wrong_answer("Too many app checks\n");
            cout << get_distance() << endl;
            continue;
        }
        else if (command == "up") {
            judge_message("up\n");
            if (!cur.can_go_up()) wrong_answer("Tried to go up when not possible\n");
            cur.go_up();
            walk_count++;
            if (walk_count > MAX_WALK) wrong_answer("Too many rooms traversed\n");

            if (cur.true_level < lca_level_cur) {
                goal.go_up();
                lca_level_cur--;
                lca_level_goal--;
                lca_offset_cur = cur.offset;
                lca_offset_goal = goal.offset;
            }
        }
        else if (command == "right") {
            judge_message("right\n");
            if (!cur.can_go_right()) wrong_answer("Tried to go right when not possible\n");
            cur.go_right();
            walk_count++;
            if (walk_count > MAX_WALK) wrong_answer("Too many rooms traversed\n");
            if (cur.true_level / c == lca_level_cur / c) {
                Position test(cur.true_level, cur.relative_level, cur.offset, r);
                int iter_counts = 0;
                while (test.true_level > lca_level_cur) {
                    iter_counts++;
                    if (iter_counts > 1000) judge_error("inf loop\n");
                    test.go_up();
                }
                lca_offset_cur = test.offset; 
            } // Check if in same "room copy"
        }
        else if (command == "left") {
            judge_message("left\n");
            if (!cur.can_go_left()) wrong_answer("Tried to go left when not possible\n");
            cur.go_left();
            walk_count++;
            if (walk_count > MAX_WALK) wrong_answer("Too many rooms traversed\n");
            if (cur.true_level / c == lca_level_cur / c) {
                Position test(cur.true_level, cur.relative_level, cur.offset, r);
                int iter_counts = 0;
                while (test.true_level > lca_level_cur) {
                    iter_counts++;
                    if (iter_counts > 1000) judge_error("inf loop\n");
                    test.go_up();
                }
                lca_offset_cur = test.offset;
            } // Check if in same "room copy"
            
        }
        else if (command == "downright") {
            judge_message("downright\n");

            if (!cur.can_go_down_right()) wrong_answer("Tried to go down right when not possible\n");
            cur.go_down_right();
            walk_count++;
            if (walk_count > MAX_WALK) wrong_answer("Too many rooms traversed\n");
            if (lca_level_cur == cur.true_level - 1) {
                // check if need to update lca values
                if (lca_level_goal == B) {
                    cout << cur.info() << endl;
                    continue; // lca goal is already goal
                }
                Position new_lca_goal(lca_level_goal, lca_level_goal % c, lca_offset_goal, r);
                new_lca_goal.up_copy_position = goal.up_copy_position;
                if (path_goal[lca_level_goal] == 0) {
                    if (!new_lca_goal.can_go_down_left()) judge_error("Invalid goal pathing\n");
                    new_lca_goal.go_down_left();
                }
                else {
                    if (!new_lca_goal.can_go_down_right()) judge_error("Invalid goal pathing\n");
                    new_lca_goal.go_down_right();
                }
                if (cur.relative_level == 0 && lca_offset_cur != lca_offset_goal) {
                    cout << cur.info() << endl;
                    continue;
                } 
                if (r.can_go(cur.relative_level, cur.offset, new_lca_goal.offset)) {
                    lca_offset_cur = cur.offset;
                    lca_level_cur = cur.true_level;
                    lca_offset_goal = new_lca_goal.offset;
                    lca_level_goal = new_lca_goal.true_level;
                    goal.true_level = new_lca_goal.true_level;
                    goal.offset = new_lca_goal.offset;
                    goal.relative_level = new_lca_goal.relative_level;
                    goal.up_copy_position = new_lca_goal.up_copy_position;
                }
            }
        }
        else if (command == "downleft") {
            judge_message("downleft\n");

            if (!cur.can_go_down_left()) wrong_answer("Tried to go down left when not possible\n");
            cur.go_down_left();
            walk_count++;
            if (walk_count > MAX_WALK) wrong_answer("Too many rooms traversed\n");
            if (lca_level_cur == cur.true_level - 1) {
                // check if need to update lca values
                if (lca_level_goal == B) {
                    cout << cur.info() << endl;
                    continue;
                }; // lca goal is already goal

                Position new_lca_goal(goal.true_level, goal.relative_level, goal.offset, r);
                new_lca_goal.up_copy_position = goal.up_copy_position;
                if (path_goal[lca_level_goal] == 0) {
                    if (!new_lca_goal.can_go_down_left()) judge_error("Invalid goal pathing (trying to go downleft)\n");
                    new_lca_goal.go_down_left();
                }
                else {
                    if (!new_lca_goal.can_go_down_right()) judge_error("Invalid goal pathing (trying to go downright)\n");
                    new_lca_goal.go_down_right();
                }
                if (cur.relative_level == 0 && lca_offset_cur != lca_offset_goal) {
                    cout << cur.info() << endl;
                    continue;
                }

                if (r.can_go(cur.relative_level, cur.offset, new_lca_goal.offset)) {
                    lca_offset_cur = cur.offset;
                    lca_level_cur = cur.true_level;
                    lca_offset_goal = new_lca_goal.offset;
                    lca_level_goal = new_lca_goal.true_level;
                    goal.true_level = new_lca_goal.true_level;
                    goal.offset = new_lca_goal.offset;
                    goal.relative_level = new_lca_goal.relative_level;
                    goal.up_copy_position = new_lca_goal.up_copy_position;
                }
            }
            

        }
        else if (command == "here") {
            if (get_distance() == 0) accept(); // :D
            else wrong_answer("Said here when not here\n");
        }
        else {
            wrong_answer("Invalid command\n");
        }
        cout << cur.info() << endl;
    }
}


void run_full() {
    int n;
    int A = 0, B = 0; 
    vector<int> path;
    vector<int> goal;
    judge_message("running full\n");

    judge_in >> n;
    judge_in >> A;
    path.resize(A);
    rep(i,0,A) judge_in >> path[i];
    judge_in >> B;
    goal.resize(B);
    rep(i,0,B) judge_in >> goal[i];

    assert(B == n-1);
    rep(i,0,B) assert(goal[i] == 0);

    judge_message("cleared asserts\n");

    set<int> path_ones;
    rep(i,0,A) if (path[i] == 1) {
        path_ones.insert(i);
    }

    auto can_go_up = [&]() {
        return (A != 0);
    };

    auto up = [&]() {
        if (A == 0) judge_error("tried to go up when impossible\n");
        if (path[A - 1] == 1) path_ones.erase(A-1);
        path.pop_back();
        A--;
    };

    auto can_go_right = [&]() { // worst case O(n)
        if (A == 0) return false;
        int i = A - 1;
        while (path[i] == 1) {
            i--;
            if (i < 0) return false;
        }
        return true;
    };

    auto right = [&]() {
        if (A == 0) judge_error("Tried to go right when impossible\n");
        int i = A-1;
        while (path[i] == 1) {
            path_ones.erase(i);
            path[i] = 0;
            i--;
            if (i < 0) judge_error("tried to go right when impossible\n");
        }
        path[i] = 1;
        path_ones.insert(i);
    };

    auto can_go_left = [&]() {
        if (A == 0) return false;
        int i = A - 1;
        while (path[i] == 0) {
            i--;
            if (i < 0) return false;
        }
        return true;
    };

    auto left = [&]() {
        if (A == 0) judge_error("Tried to go right when impossible\n");
        int i = A-1;
        while (path[i] == 0) {
            path[i] = 1;
            path_ones.insert(i);
            i--;
            if (i < 0) judge_error("tried to go left when impossible\n");
        }
        path[i] = 0;
        path_ones.erase(i);
    };

    auto can_go_downleft = [&]() {
        return A < n;
    };

    auto downleft = [&]() {
        A++;
        if (A > n) judge_error("tried to go downleft when not possible\n");
        path.push_back(0);
    };
    
    auto can_go_downright = [&]() {
        return A < n;
    };

    auto downright = [&]() {
        A++;
        if (A > n) judge_error("tried to go downright when not possible\n");
        path.push_back(1);
        path_ones.insert(A-1);
    };

    auto distance = [&]() -> ll {
        if (path_ones.size() == 0) return B - A;
        else {
            int first_one = *path_ones.begin();
            ll distance = 1;

            for (int i = first_one+1; i < A; i++) {
                distance *= 2;
                if (path[i] == 1) distance++;
                if (distance > 1e9) return -1;
            }
            distance += B - A;
            if (distance > 1e9) return -1;
            return distance;
        }
    };
    
    auto info = [&]() {
        string _ = "00000";
        if (can_go_up()) _[0] = '1';
        if (can_go_right()) _[1] = '1';
        if (can_go_downright()) _[2] = '1';
        if (can_go_downleft()) _[3] = '1';
        if (can_go_left()) _[4] = '1';
        return _;
    };

    int app_count = 0, walk_count = 0;
    cout << info() << endl;

    /*   INTERACTION STARTS HERE   */
    judge_message("starting interaction\n");

    string command;

    while (true) {
        cin >> command;
        
        if (command == "app") {
            app_count++;
            if (app_count > MAX_APP) wrong_answer("Too many app calls");
            cout << distance() << endl;
        }
        else if (command == "up") {
            judge_message("go up\n");
            walk_count++;
            if (!can_go_up()) wrong_answer("Tried to go up when impossible");
            up();
            cout << info() << endl;
        }
        else if (command == "right") {
            walk_count++;
            if (!can_go_right()) wrong_answer("Tried to go right when impossible");
            right();
            cout << info() << endl;
        }
        else if (command == "downright") {
            walk_count++;
            if (!can_go_downright()) wrong_answer("Tried to go downright when impossible");
            downright();
            cout << info() << endl;
        }
        else if (command == "downleft") {
            walk_count++;
            if (!can_go_downleft()) wrong_answer("Tried to go downleft when impossible");
            downleft();
            cout << info() << endl;
        }
        else if (command == "left") {
            walk_count++;
            if (!can_go_left()) wrong_answer("Tried to go left when impossible");
            left();
            cout << info() << endl;
        }
        else if (command == "here") {
            if (distance() == 0) accept();
            else wrong_answer("Said here when not here");
        }
        else {
            wrong_answer("Invalid command");
        }
        if (walk_count > MAX_WALK) wrong_answer("Too many room traversals\n");
        judge_message("completed command\n");
    }
}



int main(int argc, char **argv) {
    init_io(argc, argv);

    int type;
    judge_in >> type;
    judge_message("type = %d\n", type);
    /*
    TYPES:
    type = 1: Copy same structure downward
        c n                     c = number of floors in copy structure, n = number of floors total
        1
        x x
        x x x x
        x x x x x x x x         1 if room else 0
        ...                     copies are created as left child on each leaf 1
        A
        0 0 1 1 0 1 0 1         road down to start
        B
        0 1 0 0                 road down to goal


    type = 2: No blocked rooms
    n                           n = number of floors
    A                           length of path to start
    0 1 0 1 0 0                 path to start
    B                           length of path to goal, needs to be = n
    0 0 0 0 0 0                 path to goal, needs all 0
    */

    if (type == 1) run_copy_down();
    if (type == 2) run_full();

}
