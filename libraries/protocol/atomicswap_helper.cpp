#include <scorum/protocol/atomicswap_helper.hpp>

#include <fc/crypto/base58.hpp>
#include <fc/crypto/sha512.hpp>
#include <fc/crypto/ripemd160.hpp>
#include <sstream>

namespace scorum {
namespace protocol {
namespace atomicswap {

std::string get_secret_packed(const std::string& secret)
{
    const size_t entropy_percent = (size_t)50;
    FC_ASSERT(entropy_percent > 0);
    size_t entropy = secret.size();
    // get value in [entropy_percent, 2*entropy_percent - 1]
    entropy = entropy_percent + entropy % entropy_percent;
    ++entropy; // increase value for [entropy_percent + 1, 2*entropy_percent]
    fc::sha512 hash = fc::sha512().hash(secret);
    // devide to 2*entropy_percent to get coefficient in (0.5, 1]
    return fc::to_base58(hash.data(), hash.data_size() * entropy / entropy_percent / (size_t)2);
}

void validate_secret_hash(const std::string& secret_hash)
{
    fc::ripemd160 fmt;
    FC_ASSERT(secret_hash.size() == fmt.data_size() * 2, "Invalid hash format. It must be in hex RIPEMD160 format");
    try
    {
        fmt = fc::ripemd160(secret_hash);
    }
    FC_CAPTURE_AND_RETHROW((secret_hash))
}

std::string get_secret_hash(const std::string& secret)
{
    fc::ripemd160 encode;
    return encode.hash(secret).str();
}

fc::sha256
get_contract_hash_obj(const account_name_type& from, const account_name_type& to, const std::string& secret_hash)
{
    std::stringstream store;
    store << from << to << secret_hash;
    return fc::sha256().hash(store.str());
}

std::string
get_contract_hash_hex(const account_name_type& from, const account_name_type& to, const std::string& secret_hash)
{
    return get_contract_hash_obj(from, to, secret_hash).str();
}

hash_index_type
get_contract_hash(const account_name_type& from, const account_name_type& to, const std::string& secret_hash)
{
    fc::sha256 encode = get_contract_hash_obj(from, to, secret_hash);

    // pack 256-bit binary data to 32-bt fixed string
    hash_index_type ret;
    // check if somebody change hash index_type size or sha256 impl
    FC_ASSERT(encode.data_size() == sizeof(ret.data));
    memcpy((char*)&ret.data, encode.data(), encode.data_size());

    ret.data = boost::endian::big_to_native(ret.data);

#ifdef IS_TEST_NET
    std::stringstream print;
    print << "Contract hash for ";
    print << from << "," << to << "," << secret_hash << " = ";
    print << get_contract_hash_hex(from, to, secret_hash);
    ulog(print.str());
#endif
    return ret;
}
}
}
}
