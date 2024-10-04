#include "player.h"

Player::Player(const std::string& fname, const std::string& lname,
                     const std::string& tfname, const std::string& tlname,
                     int time)
    : m_fname(fname), m_lname(lname),
      m_target_fname(tfname), m_target_lname(tlname),
      m_time(time) {}

std::string Player::fname() const {
    return m_fname;
}

std::string Player::lname() const {
    return m_lname;
}

std::string Player::tfname() const {
    return m_target_fname;
}

std::string Player::tlname() const {
    return m_target_lname;
}

int Player::time() const {
    return m_time;
}

void Player::set_target(std::string tfname, std::string tlname) {
    m_target_fname = tfname;
    m_target_lname = tlname;
}

void Player::set_time(int time) {
    m_time = time;
}