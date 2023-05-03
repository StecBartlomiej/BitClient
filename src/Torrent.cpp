#include "Torrent.hpp"

//BitTorrent::Torrent::Torrent(std::string name, std::string location, std::vector<FileItem> files,
//                     std::vector<std::string> trackers, uint32_t pieceSize, std::string pieceHashes,
//                     uint32_t blockSize, bool isPrivate)
//                     : name{std::move(name)}, location{std::move(location)}, files{std::move(files)},
//                     pieceHashes{std::move(pieceHashes)}, isPrivate{isPrivate}
//{
//
//}
BitTorrent::Torrent BitTorrent::GetTorrent(const std::filesystem::path &path)
{
    Decoder decoder(path);
    std::vector<std::string> file_param = decoder.Decode();
    Torrent torrent;

    for (auto idx = file_param.begin(); idx != file_param.end(); ++idx)
    {

    }
}
