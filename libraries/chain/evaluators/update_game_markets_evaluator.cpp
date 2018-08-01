#include <scorum/chain/evaluators/update_game_markets_evaluator.hpp>
#include <scorum/chain/data_service_factory.hpp>

namespace scorum {
namespace chain {
update_game_markets_evaluator::update_game_markets_evaluator(data_service_factory_i& services)
    : evaluator_impl<data_service_factory_i, update_game_markets_evaluator>(services)
{
}

void update_game_markets_evaluator::do_apply(const operation_type& op)
{
}
}
}