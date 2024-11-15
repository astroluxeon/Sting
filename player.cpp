#include "player.h"

Player::Player(const std::string& fname, const std::string& lname,
                     const std::string& tfname, const std::string& tlname,
                     const std::string instagram, const std::string tinstagram,
                     int time)
    : m_fname(fname), m_lname(lname),
      m_tfname(tfname), m_tlname(tlname),
      m_instagram(instagram), m_tinstagram(tinstagram), m_time(time) {}

std::string Player::fname() const {
    return m_fname;
}

std::string Player::lname() const {
    return m_lname;
}

std::string Player::tfname() const {
    return m_tfname;
}

std::string Player::tlname() const {
    return m_tlname;
}

std::string Player::instagram() const {
    return m_instagram;
}

std::string Player::tinstagram() const {
    return m_tinstagram;
}


int Player::time() const {
    return m_time;
}

void Player::setTarget(std::string tfname, std::string tlname, std::string tinstagram) {
    m_tfname = tfname;
    m_tlname = tlname;
    m_tinstagram = tinstagram;
}

void Player::setTime(int time) {
    m_time = time;
}