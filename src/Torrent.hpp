#ifndef BITCLIENT_TORRENT_HPP
#define BITCLIENT_TORRENT_HPP

#include <string>
#include <vector>
#include <cinttypes>

namespace BitTorrent
{
    struct Tracker
    {
        std::string address;
    };

    struct FileInfo
    {
        uint32_t piece_length;
        std::string pieces;
        int length;
        std::string name;
        bool isPrivate;
    };

    struct Torrent
    {
        std::vector<Tracker> announce;
        std::string comment;
        std::string createdBy;
        std::string creationDate;
        std::vector<FileInfo> filesInfo;
        std::string encoding;
    };
}

#endif //BITCLIENT_TORRENT_HPP
