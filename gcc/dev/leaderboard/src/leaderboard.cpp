
// modules/apps/leadersboard.cpp
#include <include/leaderboard.hpp>

//--------------------------------------------
void Leaderboard::set_score(
    std::string name, int score
) {
    if (!name.empty() && score > 0) {
        _data.insert_or_assign(name, score);
    }
    else {
        logger.error() << "Params are not compatibles\n";
    }
}
//--------------------------------------------
void Leaderboard::add_or_update(
    std::string name, int score
) {
    if (!name.empty() && score > 0) {
        _data[name] = score;
    }
    else {
        logger.error() << "Params are not compatibles\n";
    }
}
//--------------------------------------------
std::optional<int> Leaderboard::score_of(const std::string& name) const {
    auto it = _data.find(name);
    if (it != _data.end()) {
        return it->second;
    }
    else {
        return std::nullopt;
    }
}

//--------------------------------------------
namespace bp = board::parser;
bp::LeaderboardResults Leaderboard::top(std::size_t amount) const {
    bp::LeaderboardResults results_copy(
        _data.begin(), _data.end()
    ); // kopia

    std::sort(results_copy.begin(),results_copy.end(),
        [](bp::BoardResult prev, bp::BoardResult next) {
            return prev.second > next.second;
        }
    );
    bp::LeaderboardResults top_scores(
        results_copy.begin(), results_copy.begin() + amount
    );
    return top_scores;
}
//--------------------------------------------
void Leaderboard::print(std::ostream& os, std::size_t n) const {
    std::string line;
    int index = 1;
    bp::LeaderboardResults results = top(n);
    for (const auto&[name, score]: results) {
        os << index++ << ") " << name << " " << score << "\n";
    }
}
//--------------------------------------------
std::optional<double> Leaderboard::mediana() const {
    if (_data.empty()) return std::nullopt;
   
    std::vector<int> scores;
    for(auto& [name, score]: _data)
        scores.push_back(score);

    std::sort(scores.begin(), scores.end());
    std::size_t amount = scores.size();
    if (amount % 2 == 1) {
        return static_cast<double>(scores[amount / 2]);
    }
    else{
        return (
            scores[amount / 2 - 1] + scores[amount / 2]
        ) / 2.0;
    }
}
//--------------------------------------------
std::optional<double> Leaderboard::average() const {
    if (_data.empty()) return std::nullopt;
   
    std::vector<int> scores;
    for(auto& [name, score]: _data)
        scores.push_back(score);
    double sum = 0.0;
    for (const auto& [name, score] : _data)
        sum += score;
    return sum / _data.size();
}
//--------------------------------------------
