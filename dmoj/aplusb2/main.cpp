#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>
#include <algorithm>

namespace mj {
    class Integer {
    public:
        Integer();

        explicit Integer(std::string str_val);

        Integer operator+() const;

        Integer operator-() const;

        Integer operator+(const Integer &that) const;

        Integer operator-(const Integer &that) const;

        Integer &operator+=(const Integer &that);

        Integer &operator-=(const Integer &that);

        bool operator==(const Integer &that) const;

        std::string str() const;

        typedef uint64_t block_t;
    private:
        static constexpr block_t BLOCK_MAX = 1000000000;
        static constexpr std::size_t BLOCK_SIZE = 9; // BLOCK_MAX = 10^BLOCK_SIZE

        void trim_blocks();

        void invert();

        std::vector<block_t> m_blocks;
        bool m_sign;
    };

    std::string remove_leading_zeros(const std::string &str_val);
    std::string add_leading_zeros(const std::string &str_val, std::size_t length);
    bool is_integer(const std::string &str_val);
}

std::string mj::remove_leading_zeros(const std::string &str_val) {
    std::size_t i = 0;

    while (i < str_val.size() && str_val[i] == '0')
        i++;

    return str_val.substr(i);
}

std::string mj::add_leading_zeros(const std::string &str_val, std::size_t length) {
    assert(length >= str_val.size());

    std::string leading_zeros(length - str_val.size(), '0');

    return leading_zeros + str_val;
}

bool mj::is_integer(const std::string &str_val) {
    if (str_val.empty())
        return false;

    if (!std::isdigit(str_val[0]) && str_val[0] != '-')
        return false;

    for (std::size_t i = 1; i < str_val.size(); i++)
        if (!std::isdigit(str_val[i]))
            return false;

    return true;
}

mj::Integer::Integer() : m_blocks{}, m_sign{} {}

mj::Integer::Integer(std::string str_val) : m_blocks{}, m_sign{} {
    assert(is_integer(str_val));

    bool sign;

    if ((sign = (str_val[0] == '-')))
        str_val = str_val.substr(1);

    str_val = remove_leading_zeros(str_val);
    std::reverse(str_val.begin(), str_val.end());

    for (std::size_t i = 0; i < str_val.size(); i += BLOCK_SIZE) {
        std::string block_str = str_val.substr(i, BLOCK_SIZE);
        std::reverse(block_str.begin(), block_str.end());
        m_blocks.push_back(std::stoull(block_str));
    }

    if (sign)
        invert();
}

mj::Integer mj::Integer::operator+() const {
    return Integer(*this);
}

mj::Integer mj::Integer::operator-() const {
    Integer integer(*this);
    integer.invert();
    return integer;
}

mj::Integer mj::Integer::operator+(const mj::Integer &that) const {
    return Integer(*this) += that;
}

mj::Integer mj::Integer::operator-(const mj::Integer &that) const {
    return Integer(*this) -= that;
}

mj::Integer &mj::Integer::operator+=(const mj::Integer &that) {
    bool carry = false;
    std::vector<block_t> blocks = that.m_blocks;

    std::size_t i, num_blocks = std::max(m_blocks.size(), blocks.size());

    m_blocks.resize(num_blocks, m_sign ? BLOCK_MAX - 1 : 0);
    blocks.resize(num_blocks, that.m_sign ? BLOCK_MAX - 1 : 0);

    for (i = 0; i < num_blocks; i++) {
        m_blocks[i] += blocks[i] + carry;

        if ((carry = m_blocks[i] >= BLOCK_MAX))
            m_blocks[i] -= BLOCK_MAX;
    }

    if (m_sign && that.m_sign && !carry)
        m_blocks.push_back(BLOCK_MAX - 2);
    else if (!m_sign && !that.m_sign && carry)
        m_blocks.push_back(1);
    else if ((m_sign && !that.m_sign && carry) || (!m_sign && that.m_sign && !carry))
        m_sign = !m_sign;

    trim_blocks();

    return *this;
}

mj::Integer &mj::Integer::operator-=(const mj::Integer &that) {
    bool carry = false;
    std::vector<block_t> blocks = that.m_blocks;

    std::size_t i, num_blocks = std::max(m_blocks.size(), blocks.size());

    m_blocks.resize(num_blocks, m_sign ? BLOCK_MAX - 1 : 0);
    blocks.resize(num_blocks, that.m_sign ? BLOCK_MAX - 1 : 0);

    for (i = 0; i < num_blocks; i++) {
        m_blocks[i] = BLOCK_MAX + m_blocks[i] - blocks[i] - carry;

        if (!(carry = m_blocks[i] < BLOCK_MAX))
            m_blocks[i] -= BLOCK_MAX;
    }

    if ((m_sign && that.m_sign && !carry) || (!m_sign && !that.m_sign && carry))
        m_sign = !m_sign;
    else if (m_sign && !that.m_sign && carry)
        m_blocks.push_back(BLOCK_MAX - 2);
    else if (!m_sign && that.m_sign && !carry)
        m_blocks.push_back(1);

    trim_blocks();

    return *this;
}

bool mj::Integer::operator==(const mj::Integer &that) const {
    return m_sign == that.m_sign && m_blocks == that.m_blocks;
}

std::string mj::Integer::str() const {
    if (m_blocks.empty())
        return m_sign ? "-1" : "0";

    if (m_sign) {
        return '-' + (-Integer(*this)).str();
    } else {
        std::stringstream ss;
        auto it = m_blocks.rbegin();

        ss << *it++;

        for (; it != m_blocks.rend(); it++)
            ss << add_leading_zeros(std::to_string(*it), BLOCK_SIZE);

        return ss.str();
    }
}

void mj::Integer::invert() {
    std::size_t i;
    bool found_non_zero = false;

    for (i = 0; i < m_blocks.size(); i++) {
        if (found_non_zero) {
            m_blocks[i] = BLOCK_MAX - m_blocks[i] - 1;
        } else if (m_blocks[i] != 0) {
            m_blocks[i] = BLOCK_MAX - m_blocks[i];
            found_non_zero = true;
        }
    }

    if (m_sign && !found_non_zero)
        m_blocks.push_back(1);

    if (m_sign || found_non_zero)
        m_sign = !m_sign;

    trim_blocks();
}

void mj::Integer::trim_blocks() {
    block_t redundant_val = m_sign ? BLOCK_MAX - 1 : 0;

    while (!m_blocks.empty() && m_blocks.back() == redundant_val)
        m_blocks.pop_back();
}

int N;
std::string a, b;

int main() {
    std::cin >> N;

    while (N--) {
        std::cin >> a >> b;
        mj::Integer x(a), y(b);
        std::cout << (-(-x - y)).str() << std::endl;
    }

    return 0;
}