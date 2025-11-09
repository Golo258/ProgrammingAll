

#include <utils/parse.hpp>



namespace utils::parser {
    LeaderboardResults parse_name_score_lines(
        std::string scores_input
    ){
        std::cout << " text: " << scores_input << std::endl;
        LeaderboardResults results;
        std::istringstream scores_buffor(scores_input);
        std::string buffor_line;
        while(std::getline(scores_buffor, buffor_line)){
            try{
                auto items = retrieve_scores_items(buffor_line);
                if (!items.has_value()) logger.error() << "Buffor line is not compatible\n"; 
                logger.debug() 
                    << "Items [" << items->first
                    << ", " << items->second << " ] \n";
                auto clean_name_part = clean_items_parts(items->first);
                auto clean_score_part = clean_items_parts(items->second);
                std::string cleaned_name = std::get<std::string>(clean_name_part);
                int cleaned_score =  std::get<int>(clean_score_part);
                results.push_back(
                    std::make_pair(cleaned_name, cleaned_score)
                );
            }
            catch(const ParseError::exception& parser_err){
                logger.error() << "Error cause of " << parser_err.what() << std::endl;
            }
        }
        std::cout << "\n\n\n";
        for (auto item: results){
            logger.info() << "Collected and parsed: "
                << item.first
                << ","
                << item.second
                << ". \n";
        }
        return results;
    }
    std::optional<
        std::pair<std::string, std::string>
    > retrieve_scores_items(std::string buffor_line){
        logger.debug() << "Line content " << buffor_line << std::endl;
        auto seperator_position = buffor_line.find('=');
        std::regex multiple_hashes(R"(={2,})");
        if (seperator_position == std::string::npos){
            throw ParseError("Line does not contain any = sign\n");
            return std::nullopt;
        }
        if (buffor_line.find("#") != std::string::npos){
            throw ParseError("Line contains # comment sign.\n");
            return std::nullopt;
        }
        if (std::regex_search(buffor_line, multiple_hashes)){
            throw ParseError("Line contain multiple equals signs\n");
            return std::nullopt;
        }
        std::string score_key = buffor_line
            .substr(0, seperator_position);
        std::string score_value = buffor_line
            .substr(seperator_position + 1);
        return std::make_pair(score_key, score_value);
    }
    
    std::variant<std::string, int> clean_items_parts(std::string part) {
        trim_string(part, Trim::BOTH);
        try{
            int score = std::stoi(part);
            return score;
        }
        catch (std::exception exception){
            logger.error() << "Convertion error " << exception.what() << std::endl;
        }
        logger.info() << "Trimmed string: " << part << std::endl;
        return part;
    }
    void trim_string(std::string& text, Trim side){
        const auto first = text.find_first_not_of(white_spaces_group);
        if (first == std::string::npos){
            text.clear();
            return;
        }
        const auto last = text.find_last_not_of(white_spaces_group);
        if (side == Trim::LEFT || side == Trim::BOTH) {
            text.erase(0, first);
        }
        if (side == Trim::RIGHT || side == Trim::BOTH) {
            const auto new_last = 
                (side == Trim::LEFT || side == Trim::BOTH) 
                    ? (last - first) 
                    : last;
            text.erase(new_last + 1);
        }
    }
}