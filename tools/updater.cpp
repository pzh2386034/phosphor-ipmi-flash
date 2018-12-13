/*
 * Copyright 2018 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "updater.hpp"

#include <algorithm>
#include <memory>

int updaterMain(BlobInterface* blob, DataInterface* handler,
                const std::string& imagePath, const std::string& signaturePath)
{
    /* TODO(venture): Add optional parameter to specify the flash type, default
     * to legacy for now.
     */
    std::string goalFirmware = "/flash/image";

    /* Get list of blob_ids, check for /flash/image, or /flash/tarball.
     * TODO(venture) the mechanism doesn't care, but the caller of burn_my_bmc
     * will have in mind which they're sending and we need to verify it's
     * available and use it.
     */
    std::vector<std::string> blobs = blob->getBlobList();
    auto blobInst = std::find(blobs.begin(), blobs.end(), goalFirmware);
    if (blobInst == blobs.end())
    {
        std::fprintf(stderr, "firmware goal not found!\n");
        return -1; /* throw custom exception. */
    }

    /* Call stat on /flash/image (or /flash/tarball) and check if data interface
     * is supported.
     */
    auto stat = blob->getStat(goalFirmware);
    if ((stat.blob_state & handler->supportedType()) == 0)
    {
        std::fprintf(stderr, "data interface selected not supported.\n");
        return -1; /* throw custom exception. */
    }

    return 0;
}
