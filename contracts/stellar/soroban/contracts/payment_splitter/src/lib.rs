#![no_std]

use soroban_sdk::{contract, contractimpl, contracttype, token, Address, BytesN, Env, Vec};

#[derive(Clone)]
#[contracttype]
pub enum DataKey {
    Payment(BytesN<32>),
}

#[derive(Clone)]
#[contracttype]
pub struct Split {
    pub to: Address,
    pub amount: i128,
}

#[contract]
pub struct PaymentSplitter;

fn validate_splits(splits: &Vec<Split>) {
    if splits.is_empty() {
        panic!("at least one split is required");
    }

    for split in splits.iter() {
        if split.amount <= 0 {
            panic!("split amount must be positive");
        }
    }
}

fn ensure_unpaid(env: &Env, payment_id: &BytesN<32>) {
    if env
        .storage()
        .persistent()
        .has(&DataKey::Payment(payment_id.clone()))
    {
        panic!("duplicate payment");
    }
}

#[contractimpl]
impl PaymentSplitter {
    pub fn settle_split(
        env: Env,
        token_address: Address,
        payer: Address,
        payment_id: BytesN<32>,
        splits: Vec<Split>,
    ) -> i128 {
        ensure_unpaid(&env, &payment_id);
        validate_splits(&splits);

        let token_client = token::Client::new(&env, &token_address);
        let spender = env.current_contract_address();
        let mut total_amount: i128 = 0;

        for split in splits.iter() {
            total_amount += split.amount;
            token_client.transfer_from(&spender, &payer, &split.to, &split.amount);
        }

        env.storage()
            .persistent()
            .set(&DataKey::Payment(payment_id.clone()), &true);

        env.events()
            .publish(("settle_split",), (token_address, payer, payment_id, total_amount, splits));

        total_amount
    }

    pub fn settle_balance(env: Env, token_address: Address, payment_id: BytesN<32>, splits: Vec<Split>) -> i128 {
        ensure_unpaid(&env, &payment_id);
        validate_splits(&splits);

        let token_client = token::Client::new(&env, &token_address);
        let from = env.current_contract_address();
        let mut total_amount: i128 = 0;

        for split in splits.iter() {
            total_amount += split.amount;
            token_client.transfer(&from, &split.to, &split.amount);
        }

        env.storage()
            .persistent()
            .set(&DataKey::Payment(payment_id.clone()), &true);

        env.events()
            .publish(("settle_balance",), (token_address, payment_id, total_amount, splits));

        total_amount
    }

    pub fn has_payment(env: Env, payment_id: BytesN<32>) -> bool {
        env.storage().persistent().has(&DataKey::Payment(payment_id))
    }
}

mod test;
