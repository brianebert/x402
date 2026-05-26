#![no_std]

use soroban_sdk::{contract, contractimpl, contracttype, token, Address, BytesN, Env};

#[derive(Clone)]
#[contracttype]
pub enum DataKey {
    Payment(BytesN<32>),
}

#[contract]
pub struct PaymentReceiver;

#[contractimpl]
impl PaymentReceiver {
    pub fn receive_payment(
        env: Env,
        token_address: Address,
        payer: Address,
        pay_to: Address,
        payment_id: BytesN<32>,
        amount: i128,
    ) {
        if amount <= 0 {
            panic!("amount must be positive");
        }

        if env.storage().persistent().has(&DataKey::Payment(payment_id.clone())) {
            panic!("duplicate payment");
        }

        let token_client = token::Client::new(&env, &token_address);
        let spender = env.current_contract_address();
        token_client.transfer_from(&spender, &payer, &pay_to, &amount);

        env.storage()
            .persistent()
            .set(&DataKey::Payment(payment_id.clone()), &true);

        env.events()
            .publish(("receive_payment",), (token_address, payer, pay_to, payment_id, amount));
    }

    pub fn has_payment(env: Env, payment_id: BytesN<32>) -> bool {
        env.storage().persistent().has(&DataKey::Payment(payment_id))
    }
}

mod test;
