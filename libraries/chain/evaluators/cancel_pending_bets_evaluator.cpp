#include <scorum/chain/evaluators/cancel_pending_bets_evaluator.hpp>
#include <scorum/chain/data_service_factory.hpp>
#include <scorum/chain/services/account.hpp>
#include <scorum/chain/services/pending_bet.hpp>
#include <scorum/chain/services/matched_bet.hpp>

#include <scorum/chain/betting/betting_service.hpp>

namespace scorum {
namespace chain {
cancel_pending_bets_evaluator::cancel_pending_bets_evaluator(data_service_factory_i& services,
                                                             betting_service_i& betting_service)
    : evaluator_impl<data_service_factory_i, cancel_pending_bets_evaluator>(services)
    , _account_service(services.account_service())
    , _pending_bet_svc(services.pending_bet_service())
    , _betting_svc(betting_service)
{
}

void cancel_pending_bets_evaluator::do_apply(const operation_type& op)
{
    try
    {
        _account_service.check_account_existence(op.better);
        for (const auto& id : op.bet_ids)
        {
            FC_ASSERT(_pending_bet_svc.is_exists(id), "Bet ${id} doesn't exist", ("id", id));
            FC_ASSERT(_pending_bet_svc.get_pending_bet(id).better == op.better, "Invalid better. Bet: ${0}", ("0", id));
        }

        for (const auto& id : op.bet_ids)
            _betting_svc.cancel_pending_bet(id);
    }
    FC_CAPTURE_LOG_AND_RETHROW((op))
}
}
}