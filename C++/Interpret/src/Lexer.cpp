#include "ErrorHandler.h"
#include "Lexer.h"


Lexer::Lexer(string const & file_path): m_automation(new LexingAutomation()) {
        ifstream input_stream(file_path);
        if(!input_stream)
            cout << "File " << file_path << " not found.\n";
        else
            tokenize(input_stream);
    }

void Lexer::tokenize(ifstream &input_stream) {
    string line;
    while (true) {
        getline(input_stream, line);
        if (!input_stream) break;

        m_automation->next_line();
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == '#') break;
            m_automation->next_symbol(line[i]);
        }

        m_automation->next_symbol('\n');
        if (!ErrorHandler::is_ok()) return;
    }
}

vector<Lexeme> Lexer::get_result() {
    vector<Lexeme> result = m_automation->result();
    vector<Lexeme> clean_result;
    size_t i = 0;
    while (i < result.size()) {
        clean_result.push_back(result[i]);
        if (result[i].type() == kEndofLine) {
            ++i;
            while (i < result.size() && result[i].type() == kEndofLine) ++i;
        } else ++i;
    }
    return clean_result;
}
