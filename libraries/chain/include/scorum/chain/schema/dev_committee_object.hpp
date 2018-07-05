#pragma once

#include <scorum/protocol/asset.hpp>

#include <scorum/chain/schema/scorum_object_types.hpp>

namespace scorum {
namespace chain {

using scorum::protocol::asset;
using scorum::protocol::percent_type;

class dev_committee_object : public object<dev_committee_object_type, dev_committee_object>
{
public:
    /// \cond DO_NOT_DOCUMENT
    CHAINBASE_DEFAULT_DYNAMIC_CONSTRUCTOR(dev_committee_object, (vcg_post_coefficients)(vcg_banner_coefficients))

    id_type id;

    asset sp_balance = asset(0, SP_SYMBOL);
    asset scr_balance = asset(0, SCORUM_SYMBOL);

    fc::shared_vector<percent_type> vcg_post_coefficients;
    fc::shared_vector<percent_type> vcg_banner_coefficients;

    protocol::percent_type transfer_quorum = SCORUM_COMMITTEE_TRANSFER_QUORUM_PERCENT;
    protocol::percent_type invite_quorum = SCORUM_COMMITTEE_ADD_EXCLUDE_QUORUM_PERCENT;
    protocol::percent_type dropout_quorum = SCORUM_COMMITTEE_ADD_EXCLUDE_QUORUM_PERCENT;
    protocol::percent_type change_quorum = SCORUM_COMMITTEE_QUORUM_PERCENT;
    protocol::percent_type budgets_vcg_properties_quorum = SCORUM_COMMITTEE_QUORUM_PERCENT;
};

class dev_committee_member_object : public object<dev_committee_member_object_type, dev_committee_member_object>
{
public:
    CHAINBASE_DEFAULT_CONSTRUCTOR(dev_committee_member_object)

    id_type id;
    account_name_type account;
};

typedef shared_multi_index_container<dev_committee_object,
                                     indexed_by<ordered_unique<tag<by_id>,
                                                               member<dev_committee_object,
                                                                      dev_committee_object::id_type,
                                                                      &dev_committee_object::id>>>>
    dev_committee_index;

struct by_account_name;

typedef shared_multi_index_container<dev_committee_member_object,
                                     indexed_by<ordered_unique<tag<by_id>,
                                                               member<dev_committee_member_object,
                                                                      dev_committee_member_id_type,
                                                                      &dev_committee_member_object::id>>,
                                                ordered_unique<tag<by_account_name>,
                                                               member<dev_committee_member_object,
                                                                      account_name_type,
                                                                      &dev_committee_member_object::account>>>>
    dev_committee_member_index;

} // namespace chain
} // namespace scorum

// clang-format off
FC_REFLECT(scorum::chain::dev_committee_object,
           (id)
           (sp_balance)
           (scr_balance)
           (vcg_post_coefficients)
           (vcg_banner_coefficients)
           (transfer_quorum)
           (invite_quorum)
           (dropout_quorum)
           (change_quorum)
           (budgets_vcg_properties_quorum))
// clang-format on

CHAINBASE_SET_INDEX_TYPE(scorum::chain::dev_committee_object, scorum::chain::dev_committee_index)

CHAINBASE_SET_INDEX_TYPE(scorum::chain::dev_committee_member_object, scorum::chain::dev_committee_member_index)
