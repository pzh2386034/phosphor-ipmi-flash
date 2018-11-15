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

#include "lpc_aspeed.hpp"

#include "lpc_interface.hpp"

#include <cstdint>
#include <memory>
#include <utility>

namespace blobs
{

std::unique_ptr<LpcMapperInterface> LpcMapperAspeed::createAspeedMapper()
{
    /* NOTE: considered using a joint factory to create one or the other, for
     * now, separate factories.
     */
    return std::make_unique<LpcMapperAspeed>();
}

std::pair<std::uint32_t, std::uint32_t>
    LpcMapperAspeed::mapWindow(std::uint32_t address, std::uint32_t length)
{
    return std::make_pair(0, 0);
}

} // namespace blobs