#pragma once
#include <scorum/protocol/scorum_operations.hpp>
#include <scorum/chain/evaluators/evaluator.hpp>

namespace scorum {
namespace chain {
class update_game_markets_evaluator : public evaluator_impl<data_service_factory_i, update_game_markets_evaluator>
{
public:
    using operation_type = scorum::protocol::update_game_markets_operation;

    update_game_markets_evaluator(data_service_factory_i& services);

    void do_apply(const operation_type& op);
};
}
}