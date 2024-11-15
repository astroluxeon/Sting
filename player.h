#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string m_fname;
    std::string m_lname;
    std::string m_tfname;
    std::string m_tlname;
    std::string m_instagram;
    std::string m_tinstagram;
    int m_time;

public:
    Player(const std::string& fname, const std::string& lname,
              const std::string& tfname, const std::string& tlname,
              const std::string instagram, const std::string tinstagram,
              int time);

    std::string fname() const;
    std::string lname() const;
    std::string tfname() const;
    std::string tlname() const;
    std::string instagram() const;
    std::string tinstagram() const;
    int time() const;

    void setTarget(std::string tfname, std::string tlname, std::string tinstagram);
    void setTime(int time);
};

#endif