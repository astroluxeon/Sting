#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>

inline const std::string txt_file = "list.txt";
inline const std::string txt_filef = "listf.txt";
inline const int time_limit = 28;

class Player {
private:
    std::string m_fname;
    std::string m_lname;
    std::string m_target_fname;
    std::string m_target_lname;
    int m_time;

public:
    Player(const std::string& fname, const std::string& lname,
              const std::string& tfname, const std::string& tlname,
              int time);

    std::string fname() const;
    std::string lname() const;
    std::string tfname() const;
    std::string tlname() const;
    int time() const;

    void set_target(std::string tfname, std::string tlname);
    void set_time(int time);
};

#endif