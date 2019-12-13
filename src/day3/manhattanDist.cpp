#include "manhattanDist.hpp"
#include <cstdlib>
#include <iostream>
#include <iterator>

int ManhattanDist::addRoute(const std::vector<std::string>& route)
{
    // size_t currX = 0;
    // size_t currY = 0;
    //auto posX = m_centralPortX;
    //auto posY = m_centralPortY; // static_cast<matrixCol::iterator>(
    matrixRow::iterator itX = m_centralPortX;
    int64_t indexY = 0;
    if(itX->size()) { // NOLINT readability-container-size-empty (cannot use empty() for some reason, maybe beacuse we have a list of lists of something?)
        indexY = std::distance(itX->begin(), m_centralPortY);
    }

    m_routeCnt++;

    for (const std::string& move : route) {
        switch (move.at(0)) {
        case 'U': {
            auto steps = std::stoi(move.substr(1));
            std::cout << "U " << steps << "\n";
            // Check if matrix big enough.
            auto rem = std::distance(itX, m_matrix.end());
            // If too small, add elements.
            while (rem < steps) {
                m_matrix.emplace_back();
                rem++;
            }
            while(steps-- >= 0)
            {
                //auto it = itX->begin();
                matrixCol::iterator it = itX->begin();
                std::advance(it, indexY);
                //const auto sz = it->size();
                size_t sz = 0;
                if(it->empty()) {
                    sz = 0;
                }
                else {
                    sz = it->size();
                }
                int dist = 0;
                if(sz == 0) {
                    std::cout << "It was a empty\n";
                    it->insert({m_routeCnt, dist});
                }
                else if(sz == 1) {
                    if(it->find(m_routeCnt) == it->end()) {
                        // The first time this is crossed, and not crossing itself, calculate dist.
                        dist = 99; // NOLINT cppcoreguidelines-avoid-magic-numbers
                    }
                    else {
                        // Crossed ourselves, do nothing. Or should we???
                    }
                }
                
                // Insert key + value, if key already exists nothing is changed.
                it->insert({m_routeCnt, dist});
                
                // Or add to pos 0?
                // Add coordinates + manhattan to some low-list.
            }
            break;
        }
        case 'D': {
            auto steps = std::stoi(move.substr(1));
            std::cout << "D " << steps << "\n";
            break;
        }
        case 'R': {
            auto steps = std::stoi(move.substr(1));
            std::cout << "R " << steps << "\n";
            break;
        }
        case 'L': {
            auto steps = std::stoi(move.substr(1));
            std::cout << "L " << steps << "\n";
            break;
        }
        default:
            std::cout << "Terrible, received an unparseable character: " << move.at(0) << "\n";
            break;
        }
    }

    return m_routeCnt;
}
