#pragma once

#include "blob_interface.hpp"
#include "ipmi_interface.hpp"

class BlobHandler : public BlobInterface
{
  public:
    enum BlobOEMCommands
    {
        bmcBlobGetCount = 0,
        bmcBlobEnumerate = 1,
        bmcBlobOpen = 2,
        bmcBlobRead = 3,
        bmcBlobWrite = 4,
        bmcBlobCommit = 5,
        bmcBlobClose = 6,
        bmcBlobDelete = 7,
        bmcBlobStat = 8,
        bmcBlobSessionStat = 9,
        bmcBlobWriteMeta = 10,
    };

    explicit BlobHandler(IpmiInterface* ipmi) : ipmi(ipmi){};

    /**
     * Send the contents of the payload to IPMI, this method handles wrapping
     * with the OEN, subcommand and CRC.
     *
     * @param[in] command - the blob command.
     * @param[in] payload - the payload bytes.
     * @return the bytes returned from the ipmi interface.
     */
    std::vector<std::uint8_t>
        sendIpmiPayload(BlobOEMCommands command,
                        const std::vector<std::uint8_t>& payload);

    /**
     * Retrieve the blob count.
     *
     * @return the number of blob_ids found (0 on failure).
     */
    int getBlobCount();

    /**
     * Given an index into the list of blobs, return the name.
     *
     * @param[in] index - the index into the list of blob ids.
     * @return the name as a string or empty on failure.
     */
    std::string enumerateBlob(std::uint32_t index);

    std::vector<std::string> getBlobList() override;
    StatResponse getStat(const std::string& id) override;
    std::uint16_t
        openBlob(const std::string& id,
                 blobs::FirmwareBlobHandler::UpdateFlags handlerFlags) override;

  private:
    IpmiInterface* ipmi;
};
