#![cfg(test)]

extern crate std;

use soroban_sdk::{testutils::Address as _, token, Address, BytesN, Env, Vec};

use crate::{PaymentSplitter, Split};

#[test]
fn settles_multiple_recipients_atomically() {
    let env = Env::default();
    let contract_id = env.register_contract(None, PaymentSplitter);
    let contract = PaymentSplitterClient::new(&env, &contract_id);

    let token_admin = Address::generate(&env);
    let token_contract = env.register_stellar_asset_contract(token_admin.clone());
    let token_client = token::StellarAssetClient::new(&env, &token_contract);
    let payer = Address::generate(&env);
    let publisher = Address::generate(&env);
    let host = Address::generate(&env);
    let affiliate = Address::generate(&env);
    let payment_id = BytesN::from_array(&env, &[9; 32]);

    token_client.mint(&payer, &1_000);
    token_client.approve(&payer, &contract_id, &1_000, &200);

    let splits = Vec::from_array(
        &env,
        [
            Split {
                to: publisher.clone(),
                amount: 700,
            },
            Split {
                to: host.clone(),
                amount: 200,
            },
            Split {
                to: affiliate.clone(),
                amount: 100,
            },
        ],
    );

    let total = contract.settle_split(&token_contract, &payer, &payment_id, &splits);

    assert_eq!(total, 1_000);
    assert!(contract.has_payment(&payment_id));
    let token = token::Client::new(&env, &token_contract);
    assert_eq!(token.balance(&publisher), 700);
    assert_eq!(token.balance(&host), 200);
    assert_eq!(token.balance(&affiliate), 100);
}

#[test]
fn settles_from_contract_balance() {
    let env = Env::default();
    let contract_id = env.register_contract(None, PaymentSplitter);
    let contract = PaymentSplitterClient::new(&env, &contract_id);

    let token_admin = Address::generate(&env);
    let token_contract = env.register_stellar_asset_contract(token_admin.clone());
    let token_client = token::StellarAssetClient::new(&env, &token_contract);
    let token = token::Client::new(&env, &token_contract);
    let payer = Address::generate(&env);
    let publisher = Address::generate(&env);
    let host = Address::generate(&env);
    let affiliate = Address::generate(&env);
    let payment_id = BytesN::from_array(&env, &[7; 32]);

    token_client.mint(&payer, &1_000);
    token.transfer(&payer, &contract_id, &1_000);

    let splits = Vec::from_array(
        &env,
        [
            Split {
                to: publisher.clone(),
                amount: 700,
            },
            Split {
                to: host.clone(),
                amount: 200,
            },
            Split {
                to: affiliate.clone(),
                amount: 100,
            },
        ],
    );

    let total = contract.settle_balance(&token_contract, &payment_id, &splits);

    assert_eq!(total, 1_000);
    assert!(contract.has_payment(&payment_id));
    assert_eq!(token.balance(&contract_id), 0);
    assert_eq!(token.balance(&publisher), 700);
    assert_eq!(token.balance(&host), 200);
    assert_eq!(token.balance(&affiliate), 100);
}

#[test]
#[should_panic(expected = "duplicate payment")]
fn rejects_duplicate_payment_id() {
    let env = Env::default();
    let contract_id = env.register_contract(None, PaymentSplitter);
    let contract = PaymentSplitterClient::new(&env, &contract_id);

    let token_admin = Address::generate(&env);
    let token_contract = env.register_stellar_asset_contract(token_admin.clone());
    let token_client = token::StellarAssetClient::new(&env, &token_contract);
    let payer = Address::generate(&env);
    let recipient = Address::generate(&env);
    let payment_id = BytesN::from_array(&env, &[3; 32]);

    token_client.mint(&payer, &100);
    token_client.approve(&payer, &contract_id, &100, &200);

    let splits = Vec::from_array(
        &env,
        [Split {
            to: recipient,
            amount: 100,
        }],
    );

    contract.settle_split(&token_contract, &payer, &payment_id, &splits);
    contract.settle_split(&token_contract, &payer, &payment_id, &splits);
}
