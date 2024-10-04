#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>

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