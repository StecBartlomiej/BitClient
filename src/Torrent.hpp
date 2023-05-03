#ifndef BITCLIENT_TORRENT_HPP
#define BITCLIENT_TORRENT_HPP

#include "BEncoding.hpp"

#include <string>
#include <vector>
#include <cinttypes>

namespace BitTorrent
{
    struct Tracker
    {
        std::string address;
    };

    struct FileItem
    {
        std::string path;
        uint32_t size;
        uint32_t offset;
    };

    class Torrent
    {
    public:
        Torrent() = default;
        Torrent(std::string name,  std::string location, std::vector<FileItem> files, std::vector<std::string> trackers,
                uint32_t pieceSize, std::string pieceHashes = "", uint32_t blockSize = 16384u, bool isPrivate = false);


    public:
        std::string name;
        bool isPrivate;
        std::vector<FileItem> files;

        std::string fileDirectory;
        std::string downloadDirectory;

        std::vector<Tracker> trackers;
        std::string comment;
        std::string createdBy;
        std::string creationDate;

        // SHA1 20 UTF8 char for each piece
        std::vector<std::string> pieceHashes;

        uint32_t blockSize;
        uint32_t pieceSize;
        uint32_t totalSize;
    };

    [[nodiscard]] Torrent GetTorrent(const std::filesystem::path &path);
}

#endif //BITCLIENT_TORRENT_HPP
