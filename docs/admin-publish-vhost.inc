    <Location "/api/vhosts/publish">
        X402 On
        X402Scheme exact
        X402Network stellar:testnet
        X402Asset CBIELTK6YBZJU5UP2WWQEUCYKLPU6AUNZ2BQ4WWFEIE3USCIHMXQDAMA
        X402Amount 1000000
        X402Description "Publish a cryptify.shop store vhost"
        X402MimeType application/json
        X402Mechanism stellar
        X402SettlementMode facilitator
        X402FacilitatorURL https://channels.openzeppelin.com/x402/testnet
        X402FacilitatorAPIKeyFile /etc/apache2/x402-secrets/facilitator.key
        X402StellarLocalBackend inprocess
        X402StellarConfigDir /etc/apache2/x402-stellar
        X402StellarSourceAccount operator_demo_split
        X402StellarRpcURL https://soroban-testnet.stellar.org:443
        X402StellarNetworkPassphrase "Test SDF Network ; September 2015"
        X402TimeoutSeconds 30
        X402PaymentIdentifier required
        X402Stakeholder admin 3000 GCBUNUZEIOC3FEOTGZQU53KGUK47Q5BBJOCANX45IN6XAZBWTPFK6DWO
    </Location>

    ProxyPass /api/vhosts/publish http://127.0.0.1:8017/internal/vhosts/publish
    ProxyPassReverse /api/vhosts/publish http://127.0.0.1:8017/internal/vhosts/publish
