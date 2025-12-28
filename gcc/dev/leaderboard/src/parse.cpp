

#include <include/parse.hpp>
namespace bp = board::parser;
//--------------------------------------------
bp::LeaderboardResults bp::parse_name_score_lines(
    std::string scores_input
){
    bp::LeaderboardResults results;
    std::istringstream scores_buffor(scores_input);
    std::string buffor_line;
    while(std::getline(scores_buffor, buffor_line)) {
        try {
            auto items = bp::retrieve_scores_items(buffor_line);
            if (!items){
                logger.error() << "Buffor line is not compatible\n"; 
                continue;
            } 
            auto name_value  = clean_items_parts(items->first);
            auto score_value = clean_items_parts(items->second);
            
            if(!std::holds_alternative<std::string>(name_value)
                || !std::holds_alternative<int>(score_value)
            ){
                logger.error() << "Type missmatch after cleanbp\n";
                continue;
            }
            std::string cleaned_name = std::get<std::string>(name_value);
            int cleaned_score =  std::get<int>(score_value);

            results.emplace_back(cleaned_name, cleaned_score);
        }
        catch(const ParseError::exception& parser_err) {
            logger.error() << "Error cause of " << parser_err.what() << std::endl;
        }
    }
    std::cout << "\n\n\n";
    for (auto& [n, s] : results) {
        logger.info() << "Collected and parsed: " << n << ", " << s << ".\n";
    }
    return results;
}
//--------------------------------------------
std::optional<
    std::pair<std::string, std::string>>
bp::retrieve_scores_items(std::string buffor) {
        auto sep_pos = buffor.find('=');
        if (sep_pos == std::string::npos) {
            throw bp::ParseError("Line does not contain any = sign\n");
        }

        std::regex multiple_hashes(R"(={2,})");
        if (std::regex_search(buffor, multiple_hashes)) {
            throw bp::ParseError("Line contain multiple equals signs\n");
        }

        if (buffor.find("#") != std::string::npos) {
            throw bp::ParseError("Line contains # comment sign.\n");
        }
        
        std::string score_key = buffor.substr(0, sep_pos);
        std::string score_value = buffor.substr(sep_pos + 1);
        return std::make_pair(
            std::move(score_key), 
            std::move(score_value)
        );
    }
//--------------------------------------------
std::variant<std::string, int> bp::clean_items_parts(
    std::string part
) {
    bp::trim_string(part, bp::Trim::BOTH);
    try {
        size_t id_x{};
        int value = std::stoi(part, &id_x);
        if (id_x == part.size() )
            return value;
    }
    catch (std::exception exception) {
        logger.error() << "Convertion error " << exception.what() << std::endl;
    }
    return part;
}
//--------------------------------------------
void bp::trim_string(std::string& text, bp::Trim side) {
    const auto first = text.find_first_not_of(
        bp::white_spaces_group);
    if (first == std::string::npos) {
        text.clear();
        return;
    }
    const auto last = text.find_last_not_of(bp::white_spaces_group);
    if (side == bp::Trim::LEFT || side == bp::Trim::BOTH) {
        text.erase(0, first);
    }
    if (side == bp::Trim::RIGHT || side == bp::Trim::BOTH) {
        const auto new_last = 
            (side == bp::Trim::LEFT || side == bp::Trim::BOTH) 
                ? (last - first) : last;
        text.erase(new_last + 1);
    }
}
//--------------------------------------------
