#include "candidate.h"

Candidate::Candidate(const std::string& fname, const std::string& lname,
                     const std::string& tfname, const std::string& tlname,
                     int time)
    : m_fname(fname), m_lname(lname),
      m_target_fname(tfname), m_target_lname(tlname),
      m_time(time) {}

std::string Candidate::fname() const {
    return m_fname;
}

std::string Candidate::lname() const {
    return m_lname;
}

std::string Candidate::tfname() const {
    return m_target_fname;
}

std::string Candidate::tlname() const {
    return m_target_lname;
}

int Candidate::time() const {
    return m_time;
}

void Candidate::set_target(std::string tfname, std::string tlname) {
    m_target_fname = tfname;
    m_target_lname = tlname;
}

void Candidate::set_time(int time) {
    m_time = time;
}