// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Data.h"
#include "rust/bindgen/WalletCoreRSBindgen.h"

#include <cassert>

namespace TW::Base32 {

/// Decode Base32 string, return bytes as Data
/// alphabet: Optional alphabet, if missing, default ALPHABET_RFC4648
inline bool decode(const std::string& encoded_in, Data& decoded_out, const char* alphabet_in = nullptr) {
    if (encoded_in.empty()) {
        return true;
    }
    auto decoded = Rust::decode_base32(encoded_in.c_str(), alphabet_in, false);
    if (decoded.data == nullptr || decoded.size == 0) {
        return false;
    }
    Data decoded_vec(&decoded.data[0], &decoded.data[decoded.size]);
    std::free(decoded.data);
    decoded_out = decoded_vec;
    return true;
}


/// Encode bytes in Data to Base32 string
/// alphabet: Optional alphabet, if missing, default ALPHABET_RFC4648
inline std::string encode(const Data& val, const char* alphabet = nullptr, bool padding = false) {
    auto* encoded = Rust::encode_base32(val.data(), val.size(), alphabet, padding);
    std::string encoded_str(encoded);
    Rust::free_string(encoded);
    return encoded_str;
}

} // namespace TW::Base32
