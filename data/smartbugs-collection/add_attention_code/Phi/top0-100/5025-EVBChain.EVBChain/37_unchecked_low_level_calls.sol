 

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
library SafeMath {
  function mul(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a * b;
    assert(a == 0 || c / a == b);
    return c;
  }

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract ERC20Basic {
  uint256 public totalSupply;
  event Transfer(address indexed from, address indexed to, uint256 value);
}

contract BasicToken is ERC20Basic {
  using SafeMath for uint256;

  mapping(address => uint256) balances;
}

contract StandardToken is BasicToken {}

contract EVBChain is StandardToken {

  string public constant name = "EVC Chain";
  string public constant symbol = "EVC";
  uint8 public constant decimals = 18;
  uint256 public constant INITIAL_SUPPLY = 1000000000 * (10 ** uint256(decimals));

  function EVBChain() public {
    totalSupply = INITIAL_SUPPLY;

    balances[0xFA3aA02539d1217fe6Af1599913ddb1A852f1934] = 320000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0xFA3aA02539d1217fe6Af1599913ddb1A852f1934, 320000000 * (10 ** uint256(decimals)));

    balances[0xD5345443886e2188e63609E77EA73d1df44Ea4BC] = 480000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender,0xD5345443886e2188e63609E77EA73d1df44Ea4BC, 480000000 * (10 ** uint256(decimals)));

    balances[0xFAc21518f4C669dE487b2BC7337Db428E74E76F2] = 200000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0xFAc21518f4C669dE487b2BC7337Db428E74E76F2, 200000000 * (10 ** uint256(decimals)));
  }
}
