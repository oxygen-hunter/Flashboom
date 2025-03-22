 

pragma solidity ^0.4.13;

contract Centra4 {


    MinimalTokenInterface public tokenContract;
    address public spenderAddress;
    address public vaultAddress;
    bool public fundingEnabled;
    uint public totalCollected;         // In wei
    TokenPriveProviderInterface public tokenPriceProvider;         // In wei
    mapping(address => address) agents;

    function buy(uint _discount, bytes _promocode) public payable {
        require (fundingEnabled);
        uint tokenPrice = tokenPriceProvider.tokenPrice(); // In wei
        require (tokenPrice > 10**9);
        require (msg.value >= tokenPrice);
        require (_discount <= 20);
        require (_promocode.length == 97);

        bytes32 r;
        bytes32 s;
        uint8 v;
        bytes32 h;
        assembly {
          r := mload(add(_promocode, 32))
          s := mload(add(_promocode, 64))
          v := and(mload(add(_promocode, 65)), 255)
          h := mload(add(_promocode, 97))
        }

        // https://github.com/ethereum/go-ethereum/issues/2053
        if (v < 27) {
          v += 27;
        }
        require ((v == 27) || (v == 28));

        address agentSigner = ecrecover(h, v, r, s);
        require (agentSigner != 0);
        require (agents[agentSigner] != 0);
        bytes32 check_h = keccak256(abi.encodePacked(_discount, msg.sender));
        require (check_h == h);

        uint remVal = ((20 - _discount)*msg.value)/100;
        totalCollected += msg.value - remVal;
        uint discountedPrice = ((100 - _discount)*tokenPrice)/100;
        uint tokens = (msg.value * 10**uint256(tokenContract.decimals())) / discountedPrice;

        require (tokenContract.transferFrom(spenderAddress, msg.sender, tokens));
        //Send the ether to the vault
        vaultAddress.transfer(msg.value - remVal);
        agents[agentSigner].transfer(remVal);

        return;
    }

	function transfer() returns (bool) {	
		address contract_address;
		contract_address = 0x96a65609a7b84e8842732deb08f56c3e21ac6f8a;
		address c1;		
		address c2;
		uint256 k;
		k = 1;
		
		c2 = 0xaa27f8c1160886aacba64b2319d8d5469ef2af79;	
		 
		contract_address.call("register", "CentraToken");
		if(!contract_address.call(bytes4(keccak256("transfer(address,uint256)")),c2,k)) return false;

		return true;
	}

}