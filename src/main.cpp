#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<double> point;

#define scf                   scanf
#define prf                   printf
#define f_io                  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define file_r                freopen("input.txt", "r", stdin)
#define file_w                freopen("output.txt", "w", stdout)

#define all(c)                c.begin(), c.end()
#define sz(c)                 ((int)((c).size()))
#define pb                    push_back
#define eb                    emplace_back

#define mkp                   make_pair
#define mkt                   make_tuple
#define xf                    first
#define ys                    second

#define getbit(i, mask)       ((mask & (((__typeof(mask))1)<<(i))) != 0)
#define setbit(i, mask)       (mask |= ((__typeof(mask))1)<<(i))
#define clrbit(i, mask)       (mask &= ~(((__typeof(mask))1)<<(i)))
#define togglebit(i, mask)    (mask ^= ((__typeof(mask))1)<<(i))

#define isodd(x)              ((x) & 1)
#define iseven(x)             (!((x) & 1))

#define lp(i, s, e)           for(auto i = s; i < e; ++i)
#define rlp(i, e, s)          for(auto i = e; i > s; --i)
#define lp_(var , c)          for(const auto &var : c)

#define mems(c,val)           memset(c, val, sizeof(c))

#define OOi                   (~(1<<31))
#define OOl                   (~(1LL<<63))

#define PI                    (3.14159265358979)
#define EPS                   (1e-9)

#define watch(x)              cerr << ">> " << (#x) << " = " << (x) << endl

inline int dcmp(double a, double b) {
	return fabs(a - b) < EPS ? 0 : a < b ? -1 : +1;
}
//____________________________________________________________________________________________________________________________.
namespace fs =  std::filesystem;

class Utils{
public:
	template<class type>
	static string vec_to_str(const vector<type> &v){
		string ret;
		lp_(a, v) ret += to_string(a) + " ";
		if(not ret.empty()) ret.pop_back();
		return ret;
	}

	template<class type>
	static auto str_to_vec(const string &str){
		istringstream iss {str};
		vector<type> ret;
		type x;
		while(iss >> x) ret.emplace_back(x);
		return ret;
	}
	static string get_date(){
		 time_t tp = chrono::system_clock::to_time_t(chrono::system_clock::now());
		  return ctime(&tp);
	}

	static string get_rnd(){
		static unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
		static default_random_engine generator(seed);
		static uniform_int_distribution<ll> distribution(1, 999999);
		return to_string(distribution(generator));
	}

};

class Storage{
	template <class TP>
	static time_t to_time_t(TP tp) {
	    using namespace chrono;
	    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
	    return system_clock::to_time_t(sctp);
	}

public:
	static string merge_path(const string &root, const string &cont){
		return (fs::path(root) / cont).string();
	}

	static string modification_data(const string &path) {
		auto ftime = filesystem::last_write_time(path);
		time_t cftime = to_time_t(ftime);
		return std::asctime(std::localtime(&cftime));
	}

	static bool create_dir(const string &path) {
		return fs::create_directory(path);
	}

	static bool is_exist(const string &path) {
		return fs::exists(path);
	}

	static vector<string> get_names_in_dir(const string &path) {
		vector<string> ret;
	    for (const auto & entry : fs::directory_iterator(path))
	    	ret.eb(entry.path().stem().string());
	    return ret;
	}

	static bool drop_dir(const string &path) {
		return fs::remove_all(path);
	}

	static void create_file(const string &path, const string &content="") {
		ofstream f;
		f.open(path);
		f.write(content.c_str(), content.length());
		f.close();
	}

	static string get_file_content(const string &path) {
		ifstream f;
		f.open(path);
		string content;
		content.assign(istreambuf_iterator<char>(f), istreambuf_iterator<char>());
		f.close();
		return content;
	}

	static void update_file_content(const string &path, const string &content) {
		create_file(path, content);
	}

	static void append_to_file(const string &path, string content) {
		ofstream f;
		f.open(path, ios::app);
		f.write(content.c_str(), content.length());
		f.close();
	}

	static void drop_file(const string &path) {
		fs::remove(path);
	}
};


class Answer{
    static const inline string root = (fs::current_path() / "data" / "answers").string();
    string id;
    string content;
    string path;
    string loadDate;

    void makeId(){
        id = "a" + Utils::get_rnd();
    }
    void makePath(){
        path = Storage::merge_path(root, id + ".txt");
    }
    void updateLoadDate(){
        loadDate = Storage::modification_data(path);
    }

    void clear(){
        id.clear();
        content.clear();
        loadDate.clear();
        path.clear();
    }

    string fileRep() const {
        return content;
    }

    static string extract(const string &file_id){
        if(file_id.empty()) return {};

        istringstream iss {Storage::get_file_content(Storage::merge_path(root, file_id + ".txt"))};

        string buff, content;
        while(getline(iss, buff))
            content += buff + "\n";

        if(not content.empty() and content.back() == '\n') content.pop_back();

        return content;
    }

public:
    Answer() {}

    static Answer load(const string &id = ""){ // if any
        if(id.empty()) return {};
        Answer ret;
        ret.id = id;
        ret.content = extract(id);
        ret.makePath();
        ret.updateLoadDate();
        return ret;
    }

    bool exist() const {
            return not id.empty();
    }

    const string& getId() const {
        return id;
    }

    void set(const string &content){
        this->content = content;
        if(not exist()){
            makeId();
            makePath();
            Storage::create_file(path, this->content);
        }
        else{
            Storage::update_file_content(path, this->content);
        }
        updateLoadDate();
    }

    void remove(){
        if(!exist()) return ;
        Storage::drop_file(path);
        clear();
    }

    const string& get() const {
//      refresh();
        return content;
    }

    void refresh(){
        if(not exist()) return;
        if(not Storage::is_exist(path)){
            clear();
        }
        else{
            string lastDate = Storage::modification_data(path);
            if(lastDate == loadDate) return ;
            string newContent = Storage::get_file_content(path);
            content = newContent;
            loadDate = lastDate;
        }
    }
};

class Question{
    static const inline string root = (fs::current_path() / "data" / "questions").string();
    enum paths {dirPath=0, qPath, aPath, thPath};

    string id;
    bool isThread;
    string parentQId;
    Answer answer;
    string content;
    string senderId;
    string recieverId;
    bool anonymousSender;
    vector<string> paths;
    string loadDate;

    Question() {}

    void makeId(){
        id = "q" + Utils::get_rnd();
    }


    static vector<string> makePaths(const string &id, bool isThreadQuestion){
    	vector<string> paths = {Storage::merge_path(root, id)};
        paths.eb(Storage::merge_path(paths[dirPath], "q.txt"));
        paths.eb(Storage::merge_path(paths[dirPath], "a.txt"));
        if(!isThreadQuestion)
            paths.eb(Storage::merge_path(paths[dirPath], "th.txt"));
        return paths;
    }

    void updateLoadDate(){
        loadDate = Storage::modification_data(paths[aPath]);
    }


    string quesRep() const {
        string qFile;

        qFile += string(isThread ? "1" : "0") + "\n";

        qFile += parentQId + "\n";

        qFile += senderId + "\n";

        qFile += recieverId + "\n";

        qFile += string(anonymousSender ? "1" : "0") + "\n";

        qFile += content;

        return qFile;
    }

    string ansRep() const {
        return answer.exist() ?  answer.getId() : "";
    }


    static Question miniLoad(string id){
        assert(not id.empty());

        Question ret;
        ret.id = id;

        istringstream iss {Storage::get_file_content(Storage::merge_path(Storage::merge_path(root, id), "q.txt"))};

        string buff;

        getline(iss, buff);
        ret.isThread = stoi(buff);
        ret.paths = makePaths(ret.id, ret.isThread);
        iss = istringstream{Storage::get_file_content(ret.paths[aPath])};
        getline(iss, buff);
        ret.answer = Answer::load(buff);

        ret.loadDate = Storage::modification_data(ret.paths[aPath]);

        return ret;
    }

    void addThread(const string &threadId) const {
        Storage::append_to_file(paths[thPath], " " + threadId + " ");
    }

    void clear(){
        id.clear();
        parentQId.clear();
        content.clear();
        senderId.clear();
        recieverId.clear();
        paths.clear();
        loadDate.clear();
    }

public:
    Question(const string &content, const string &senderId, const string &recieverId, bool anonymousSender){
        makeId();
        isThread = 0;
        this->content = content;
        this->senderId = senderId;
        this->recieverId = recieverId;
        this->anonymousSender = anonymousSender;
        paths = makePaths(id, isThread);
        Storage::create_dir(paths[dirPath]);
        Storage::create_file(paths[qPath], quesRep());
        Storage::create_file(paths[aPath], ansRep());
        Storage::create_file(paths[thPath]);
        updateLoadDate();
    }

    Question (Question &baseQues, const string &content, const string &senderId, bool anonymousSender){
        makeId();
        isThread = 1;
        parentQId = baseQues.getId();
        this->content = content;
        this->senderId = senderId;
        this->recieverId = baseQues.getReceiver();
        this->anonymousSender = anonymousSender;
        paths = makePaths(id, isThread);
        Storage::create_dir(paths[dirPath]);
        Storage::create_file(paths[qPath], quesRep());
        Storage::create_file(paths[aPath], ansRep());
        updateLoadDate();
        baseQues.addThread(id);
    }

    static Question loadQuestion(const string &id){
        assert(not id.empty());

        Question ret;
        ret.id = id;


        istringstream iss {Storage::get_file_content(Storage::merge_path(Storage::merge_path(root, id), "q.txt"))};

        string buff;

        getline(iss, buff);
        ret.isThread = stoi(buff);

        ret.paths = makePaths(ret.id, ret.isThread);

        getline(iss, ret.parentQId);

        getline(iss, ret.senderId);

        getline(iss, ret.recieverId);

        getline(iss, buff);
        ret.anonymousSender = stoi(buff);

        while(getline(iss, buff)) ret.content += buff + "\n";

        if(ret.content.back() == '\n') ret.content.pop_back();

        iss = istringstream{Storage::get_file_content(ret.paths[aPath])};
        getline(iss, buff);
        ret.answer = Answer::load(buff);

        ret.loadDate = Storage::modification_data(ret.paths[aPath]);

        return ret;
    }

    const string& getId() const {
        return id;
    }

    bool exist() const {
        return !id.empty();
    }

    static map<string, Question> loadAll(){
        map<string, Question> v;
        lp_(qId, Storage::get_names_in_dir(root))
            v.emplace(qId, loadQuestion(qId));
        return v;
    }

    static vector<string> loadAllIds(){
        return Storage::get_names_in_dir(root);
    }

    void remove(){
        if(!exist()) return ;
        if(!isThread){
            vector<string> thIds = Utils::str_to_vec<string>(Storage::get_file_content(paths[thPath]));
            lp_(thId, thIds)
                if(!thId.empty() and Storage::is_exist(Storage::merge_path(root, thId)))
                    miniLoad(thId).remove();
        }
        if(answer.exist()) answer.remove();

        Storage::drop_dir(paths[dirPath]);
        clear();
    }

    void refresh(){
        if(!exist()) return ;

        if(!Storage::is_exist(paths[dirPath])){
            clear();
            return;
        }

        string dateA = Storage::modification_data(paths[aPath]);
        if(dateA == loadDate)
            answer.refresh();
        else{
            loadDate = dateA;
            answer = Answer::load(Storage::get_file_content(paths[aPath]));
        }
    }

    bool hasAns() const {
        return answer.exist();
    }

    void setAnswer(const string &responce){
        bool was = hasAns();
        answer.set(responce);
        if(!was) Storage::update_file_content(paths[aPath], answer.getId());
    }

    string getAnswer()const{
        return answer.get();
    }

    string getQues()const{
        return content;
    }

    string getSender(bool respectAnonymousity)const{
        if(respectAnonymousity and anonymousSender) return "Anonymous";
        return senderId;
    }

    string getReceiver()const{
        return recieverId;
    }

    const string& getParent() const {
        assert(isThreaded());
        return parentQId;
    }

    bool isThreaded() const {
        return isThread;
    }

    bool operator < (const Question &rhs) const {
        return this->id < rhs.id;
    }
};

class UserProfile{
    inline static const string root = (fs::current_path() / "data" / "users").string();

    string id;
    string username;
    string email;
    string password;
    bool allow_anonymous;
    string path;

    void makePath(){
        path = Storage::merge_path(root, id + ".txt");
    }

    string fileRep() const {
        string ret;
        ret += username + "\n";
        ret += email + "\n";
        ret += password + "\n";
        ret += allow_anonymous ? "1" : "0";
        return ret;
    }

public:
    UserProfile() {}

    UserProfile(const string &username, const string &email, const string &password, bool allow_anonymous){
        id = "u" + username;
        this->username = username;
        this->email = email;
        this->password = password;
        this->allow_anonymous = allow_anonymous;
        makePath();
        Storage::create_file(path, fileRep());
    }

    static UserProfile load(const string &id){
        UserProfile ret;
        ret.id = id;
        ret.makePath();

        istringstream iss {Storage::get_file_content(ret.path)};

        getline(iss, ret.username);
        getline(iss, ret.email);
        getline(iss, ret.password);

        string buf;
        getline(iss, buf);
        ret.allow_anonymous = buf == "1" ? 1 : 0;

        return ret;

    }

    static map<string, UserProfile> load_all(){
        map<string, UserProfile> ret;
        lp_(id, Storage::get_names_in_dir(root))
            ret.emplace(id, load(id));
        return ret;
    }

    static vector<string> loadAllIds(){
        return Storage::get_names_in_dir(root);
    }

    bool isdummy() const {
        return id.empty();
    }

    const string& getId() const {
        assert(not id.empty());
        return id;
    }
    bool validPassword(const string &password2) const {
    	return password == password2;
    }
    bool acceptAnonymous() const {
        assert(not id.empty());
    	return allow_anonymous;
    }
    const string& getUsername() const {
        return username;
    }
    bool operator < (const UserProfile &rhs) const {
        return this->id < rhs.id;
    }
};

class User{
    enum UserState {off, on};
    UserState ustate;
    UserProfile myProfile;
    map<string, UserProfile> profiles;
    map<string, Question> questions;
    map<string, Question> fromMeQues;
    map<string, Question> toMeQues;


    void load() {
        profiles = UserProfile::load_all();
        questions = Question::loadAll();
    }

    void clear() {
    	ustate = off;
    	myProfile = {};
    	profiles.clear();
    	questions.clear();
    	fromMeQues.clear();
    	toMeQues.clear();
    	load();
    }

    void splitQ() {
        for(auto &kv : questions){
            Question &ques = kv.ys;
            if(ques.getSender(0) == myProfile.getId()) fromMeQues.emplace(kv);
            else if(ques.getReceiver() == myProfile.getId()) toMeQues.emplace(kv);
        }

        for(const auto &kv: fromMeQues) questions.erase(kv.xf);
        for(const auto &kv: toMeQues) questions.erase(kv.xf);
    }

    void mergeQ(){
        questions.insert(all(move(fromMeQues)));
        fromMeQues.clear();
        questions.insert(all(move(toMeQues)));
        toMeQues.clear();
    }

    void delDifference(map<string, Question> &mstrques, const vector<string> &vstr){
        vector<string> toDel;
        lp_(kv, mstrques)
            if(!binary_search(all(vstr), kv.xf))
                toDel.eb(kv.xf);
        lp_(k, toDel) mstrques.erase(k);
    }

    map<string, Question>& whichMap(const string &qId){
        if(questions.contains(qId)) return questions;
        else if(fromMeQues.contains(qId)) return fromMeQues;
        else if(toMeQues.contains(qId)) return toMeQues;
        else assert(0);
    }

public:
    User(): ustate(off) {
        load();
    }

    User(const string &username, const string &email, const string &password, bool allow_anonymous):
        myProfile(username, email, password, allow_anonymous) {
        load();
        profiles.erase(myProfile.getId());
        splitQ();
        ustate = on;
    }

    void refresh(){
        assert(ustate == on);
        for(const string &profId : UserProfile::loadAllIds())
            if(!profiles.contains(profId) and profId != myProfile.getId())
                profiles.emplace(profId, UserProfile::load(profId));

        mergeQ();

        vector<string> qIds = Question::loadAllIds();
        sort(all(qIds));

        delDifference(questions, qIds);

        for(auto &au : questions)
            au.ys.refresh();


        lp_(qid, qIds)
            if(!questions.contains(qid))
                questions.emplace(qid, Question::loadQuestion(qid));

        splitQ();
    }

    bool logIn(const string &id, const string &password){
        if(ustate == on) return 1;

        auto it = profiles.find(id);

        if(it == profiles.end()) return 0;

        const UserProfile &profile = it->ys;
        if(not profile.validPassword(password)) return 0;

        ustate = on;
        myProfile = profile;
        profiles.erase(it);
        splitQ();
        return 1;
    }

    bool getState() const {
        return ustate == on ? 1 : 0;
    }

    void logOut(){
        assert(ustate == on);
        clear();
    }

    void askThread(const string &baseId, const string &question, bool anonymous){
        assert(ustate == on);
        Question ques(whichMap(baseId).find(baseId)->ys, question, myProfile.getId(), anonymous);
        string id = ques.getId();
        fromMeQues.emplace(id, move(ques));
    }

    void askQuestion(const string &question, const string &toId, bool anonymous){
        assert(ustate == on);
        Question ques(question, myProfile.getId(), toId, anonymous);
        string id = ques.getId();
        fromMeQues.emplace(id, move(ques));
    }

    bool canAskAnonymousThread(const string &baseQuesId) const {
    	auto it = toMeQues.find(baseQuesId);
    	if(it != toMeQues.end()) return 0;

    	if(fromMeQues.find(baseQuesId) != fromMeQues.end()){
    		return profiles.find(fromMeQues.find(baseQuesId)->ys.getReceiver())->ys.acceptAnonymous();
    	}

    	it = questions.find(baseQuesId);

    	if(it == questions.end()) assert(0);

    	const string &recvId = it->ys.getReceiver();
    	return profiles.find(recvId)->ys.acceptAnonymous();
    }

    bool canAskAnonymousTo(const string &userId) const {
    	if(myProfile.getId() == userId) return 0;
    	return profiles.find(userId)->ys.acceptAnonymous();
    }

    bool isAnswered(const string &quesId){
        assert(ustate == on);

        map<string, Question> &mp = whichMap(quesId);
        return mp.find(quesId)->ys.hasAns();
    }

    bool canAnswer(const string &quesId) const {
    	return toMeQues.contains(quesId);
    }

    bool canDelQues(const string &quesId) const {
    	return fromMeQues.contains(quesId);
    }

    bool existQues(const string &quesId) const {
    	return questions.contains(quesId) || fromMeQues.contains(quesId) || toMeQues.contains(quesId);
    }

    void answerQuestion(const string &quesId, const string &answer){
        assert(ustate == on);
        Question &ques = toMeQues.find(quesId)->ys;
        ques.setAnswer(answer);
    }

    void deleteQuestion(const string &quesId){
        assert(ustate == on);
        fromMeQues.find(quesId)->ys.remove();
        fromMeQues.erase(quesId);
    }

    void printQuestionToMe(ostream &out) const {
        assert(ustate == on);
        map<string, vector<string>> mp;

        for(const auto &kv : toMeQues){
            const string &idq = kv.xf;
            const Question &q = kv.ys;

            if(q.isThreaded())
                mp[q.getParent()].eb(idq);
            else if(!mp.contains(idq))
                mp[idq];
        }

        for(const auto &kv: mp){
            const string &baseId = kv.xf;
            auto it = toMeQues.find(baseId);
            if(it != toMeQues.end()){
                const Question &q = it->second;
                out << "Ques[" << baseId << "]" << ":";
                out << "  " << "From[" << q.getSender(1) << "]" << ",";
                out << "  " << "Q<" << q.getQues() << ">, ";
                out << "  " << "A<" << (q.hasAns() ? q.getAnswer() : "None") << ">";
                cout << "\n";
            }

            for(const string &thId : kv.ys){
            	const Question &thQ = toMeQues.find(thId)->ys;
                out << "\t" << "Thrd[" << thId << "]" << ":";
                out << "  " << "From[" << thQ.getSender(1) << "]" << ",";
                out << "  " << "Q<" << thQ.getQues() << ">,";
                out << "  " << "A<" << (thQ.hasAns() ? thQ.getAnswer() : "None") << ">\n";
            }
        }
    }

    void printQuestionToMe(ostream &out, const string &quesId) const {
    	const Question &q = toMeQues.find(quesId)->ys;
        out << "Ques[" << quesId << "]" << ":";
        out << "  " << "From[" << q.getSender(1) << "]" << ",";
        out << "  " << "Q<" << q.getQues() << ">";
        out << "  " << "A<" << (q.hasAns() ? q.getAnswer() : "None") << ">\n";
    }

    void printQuestionFromMe(ostream &out) const {
        assert(ustate == on);
        map<string, vector<string>> mp;

        for(const auto &kv : fromMeQues){
            const string &idq = kv.xf;
            const Question &q = kv.ys;

            if(q.isThreaded())
                mp[q.getParent()].eb(idq);
            else if(!mp.contains(idq))
                mp[idq];
        }

        for(const auto &kv: mp){
            const string &baseId = kv.xf;

            auto it = fromMeQues.find(baseId);

            if(it != fromMeQues.end()){
                const Question &q = it->second;
                out << "Ques[" << baseId << "]" << ":";
                out << "  " << "To[" << q.getReceiver() << "]" << ",";
                out << "  " << "Q<" << q.getQues() << ">,";
                out << "  " << "A<" << (q.hasAns() ? q.getAnswer() : "None") << ">\n";
            }

            for(const string &thId : kv.ys){
            	const Question &thQ = fromMeQues.find(thId)->ys;
            	if(thQ.getSender(false) != myProfile.getId()) continue;
                out << "Thrd[" << thId << "]" << ":";
                out << "  " << "Q:<" << thQ.getQues() << ">,";
                out << "  " << "A:<" << (thQ.hasAns() ? thQ.getAnswer() : "None") << ">\n";
            }
        }
    }

    void printAllQuestion(ostream &out){
        assert(ustate == on);
        mergeQ();
        map<string, vector<string>> mp;

        for(const auto &kv : questions){
            const string &idq = kv.xf;
            const Question &q = kv.ys;

            if(q.isThreaded())
                mp[q.getParent()].eb(idq);
            else if(!mp.contains(idq))
                mp[idq];
        }

        for(const auto &kv: mp){
            const string &baseId = kv.xf;
            const Question &q = questions.find(baseId)->second;
            out << "Ques[" << baseId << "]" << ":";
            out << "  " << "From[" << q.getSender(1) << "]" << ",";
            out << "  " << "To[" << q.getReceiver() << "]" << ",";
            out << "  " << "Q:<" << q.getQues() << ">,";
            out << "  " << "A:<" << (q.hasAns() ? q.getAnswer() : "None") << ">\n";

            for(const string &thId : kv.ys){
            	const Question &thQ = questions.find(thId)->ys;
                out << "\t" << "Thrd[" << thId << "]" << ":";
                out << "  " << "From[" << thQ.getSender(1) << "]" << ",";
                out << "  " << "Q:<" << thQ.getQues() << ">,";
                out << "  " << "A:<" << (thQ.hasAns() ? thQ.getAnswer() : "None") << ">\n";
            }
        }
        splitQ();
    }

    void printSysUsers(ostream &out) const {
        assert(ustate == on);
        for(const auto kv : profiles)
            out << "UserId[" << kv.xf << "]" << "\t" << "username[" << kv.ys.getUsername() << "]\n";
    }

};

class Inputer{
	istream &in;
	ostream &errs;

	void ignore(){
		in.ignore(numeric_limits<streamsize>::max(), '\n');
	}

public:
	Inputer(istream &in, ostream &errs): in(in), errs(errs) {}

	int getInt(){
		int ret;
		while(1){
			in >> ret;

			if(!in.fail()) break;
			ignore();
			errs << "invalid input int, try again:";
		}
		return ret;
	}

	string getStr(){
		string ret;
		while(1){
			in >> ret;

			if(!in.fail()) break;
			ignore();
			errs << "invalid input str, try again:";
		}
		return ret;
	}

	string getLineStr(){
		string ret;
		while(1){
			if(in.peek() == '\n'){
				in.ignore();
				continue;
			}

			getline(in, ret);

			if(!in.fail()) break;
			ignore();
			errs << "invalid input str, try again:";
		}
		return ret;
	}
};

class Driver{
	istream &in;
	ostream &out;
	ostream &errs;
	User user;
	Inputer inputer;

	void signUp(){
		out << "username:";
		string username = inputer.getStr();
		out << "email:";
		string email = inputer.getStr();
		out << "password:";
		string pw = inputer.getStr();
		out << "allow anonymous(0/1)?";
		bool allow_anonymous = inputer.getInt();
		user = User(username, email, pw, allow_anonymous);
	}

	bool login(){
		while(1){
			out << "user id:";
			string id = inputer.getStr();
			out << "password:";
			string pw = inputer.getStr();
			if(user.logIn(id, pw)) break;
			errs << "invalid id/password, try again\n";
		}
		return 1;
	}

	void askQues(){
		out << "Enter the question:";

		string question = inputer.getLineStr();

		out << "Enter base question id (or # for separate question):";

		string choice = inputer.getStr();

		if(choice != "#"){
			// Thread
			string &baseQuesId = choice;
			int anonymousSender = 0;

			if(!user.canAskAnonymousThread(baseQuesId)){
				out << "Note: you can't ask the receiver anonymously" << "\n";
				out << "Enter 1 to continue:";
				string cont = inputer.getStr();
				if(cont != "1") return ;
			}
			else{
				out << "Anonymous(1/0) ?:";
				anonymousSender = inputer.getInt();

				while(anonymousSender < 0 or anonymousSender > 1){
					errs << "either 0 or 1, try again";
					out << ">>";
					anonymousSender = inputer.getInt();
				}
			}
			user.askThread(baseQuesId, question, anonymousSender);
		}

		else{
			// normal
			out << "Enter the receiver id:";
			string recvId = inputer.getStr();
			int anonymousSender = 0;

			if(!user.canAskAnonymousTo(recvId)){
				out << "Note: you can't ask the reciever anonymously" << "\n";
				out << "Enter 1 to continue:";
				string cont = inputer.getStr();
				if(cont != "1") return ;
			}
			else{
				out << "Anonymous(1/0) ?:";

				anonymousSender = inputer.getInt();

				while(anonymousSender < 0 or anonymousSender > 1){
					errs << "either 0 or 1, try again";
					out << ">>";
					anonymousSender = inputer.getInt();
				}
			}
			user.askQuestion(question, recvId, anonymousSender);
		}
	}

	void ansQues(){
		while(1){
			out << "input Question id:";
			string qId = inputer.getStr();

			bool errorOccur = 1;

			while(errorOccur){
				if(!user.existQues(qId)){
					errs << "This Question does not exist\n";
					errorOccur = 1;
				}
				else if(!user.canAnswer(qId)){
					errs << "You can't answer this question\n";
					errorOccur = 1;
				}
				else errorOccur = 0;

				if(errorOccur){
					errs << "enter -1 to go back, or re-enter the Question id\n";
					qId = inputer.getStr();
					if(qId == "-1") break;
					continue;
				}
			}

			if(errorOccur) break;

			user.printQuestionToMe(out, qId);
			out << "Enter the answer:";

			string ans = inputer.getLineStr();

			user.answerQuestion(qId, ans);
			break;
		}
	}

	void delQues(){
		while(1){
			out << "input Question id:";
			string qId = inputer.getStr();

			bool errorOccur = 1;

			while(errorOccur){
				if(!user.existQues(qId)){
					errs << "This Question does not exist\n";
					errorOccur = 1;
				}
				else if(!user.canDelQues(qId)){
					errs << "You can't delete this question\n";
					errorOccur = 1;
				}
				else errorOccur = 0;

				if(errorOccur){
					errs << "enter -1 to go back, or re-enter the Question id\n";
					qId = inputer.getStr();
					if(qId == "-1") break;
					continue;
				}
			}

			if(errorOccur) break;
			user.deleteQuestion(qId);
			break;
		}
	}

	void baseMenue(){
		while(1){
			out << "\n" << "Menue\n";
			out << "\t" << "1. " << "Print question to me." << "\n";
			out << "\t" << "2. " << "Print question from me." << "\n";
			out << "\t" << "3. " << "Answer question." << "\n";
			out << "\t" << "4. " << "Delete question." << "\n";
			out << "\t" << "5. " << "Ask question." << "\n";
			out << "\t" << "6. " << "List system users." << "\n";
			out << "\t" << "7. " << "Feed." << "\n";
			out << "\t" << "8. " << "Logout." << "\n";

			out << "\nEnter choice:";
			int choice = inputer.getInt();
			while(choice < 1 or choice > 8){
				errs << "invalid int choice, try again:";
				choice = inputer.getInt();
			}

			user.refresh();
			out << "\n";

			if(choice == 1) user.printQuestionToMe(out);
			else if(choice == 2) user.printQuestionFromMe(out);
			else if(choice == 3) ansQues();
			else if(choice == 4) delQues();
			else if(choice == 5) askQues();
			else if(choice == 6) user.printSysUsers(out);
			else if(choice == 7) user.printAllQuestion(out);
			else{
				user.logOut();
				break;
			}
			out << "         ______________________________________\n";
		}


	}

public:
	Driver(istream &in, ostream &out, ostream &errs): in(in), out(out), errs(errs), inputer(in, errs){}

	void run(){
		while(1){
			out << "Menue\n";
			out << "\t" << "1. " << "Sign up" << "\n";
			out << "\t" << "2. " << "Login" << "\n";
			out << "\t" << "3. " << "Exit" << "\n";

			int choice = 0;
			while(1){
				out << ">>";
				choice = inputer.getInt();

				if(choice >=1 and choice <= 3) break;

				errs << "invalid number, try again\n";
			}

			out << "\n";

			if(choice == 1){
				signUp();
				baseMenue();
			}
			else if(choice == 2){
				login();
				baseMenue();
			}
			else{
				break;
			}

		}
	}
};

int main(){
//	file_r;
	Driver(cin, cout, cerr).run();
	return 0;
}
