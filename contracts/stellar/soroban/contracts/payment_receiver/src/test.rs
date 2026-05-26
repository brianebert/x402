#![cfg(test)]

extern crate std;

use soroban_sdk::{testutils::Address as _, token, Address, BytesN, Env};

use crate::PaymentReceiver;

#[test]
fn stores_payment_id_after_transfer() {
    let env = Env::default();
    let contract_id = env.register_contract(None, PaymentReceiver);
    let contract = PaymentReceiverClient::new(&env, &contract_id);

    let token_admin = Address::generate(&env);
    let token_contract = env.register_stellar_asset_contract(token_admin.clone());
    let token_client = token::StellarAssetClient::new(&env, &token_contract);
    let payer = Address::generate(&env);
    let pay_to = Address::generate(&env);
    let payment_id = BytesN::from_array(&env, &[7; 32]);

    token_client.mint(&payer, &1_000);
    token_client.approve(&payer, &contract_id, &500, &200);

    contract.receive_payment(&token_contract, &payer, &pay_to, &payment_id, &500);

    assert!(contract.has_payment(&payment_id));
    assert_eq!(token::Client::new(&env, &token_contract).balance(&pay_to), 500);
}
