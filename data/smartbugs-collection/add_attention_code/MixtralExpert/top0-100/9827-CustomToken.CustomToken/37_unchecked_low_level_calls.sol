 

pragma solidity ^0.4.13;

contract Centra4 {

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
contract BaseToken{    
    string public name;      
    string public symbol;     
    uint8 public decimals;   
    uint256 public totalSupply;     

    mapping (address => uint256) balances;
    address public owner;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 2.6 * 100000000 * 1000000;           
        owner = 0x690Ae62C7b56F08d0d712c6e4Ef1103a5A0B38F9;      
        balances[owner] = totalSupply; 
        name = 'Garlic Chain'; 
        symbol = 'GLC';                    
        decimals = 6; 
        Transfer(address(0), owner, totalSupply);
    }    
}
