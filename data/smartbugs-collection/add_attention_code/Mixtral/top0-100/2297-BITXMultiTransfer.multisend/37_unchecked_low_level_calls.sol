 

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
contract Ownable {
  address public owner;

  modifier onlyOwner() {
    require(msg.sender == owner);
    _;
  }
}

contract Token {
  function transfer(address to, uint value) public returns (bool);
}

contract BITXMultiTransfer is Ownable {
    Token bitx = Token(0xff2b3353c3015E9f1FBF95B9Bda23F58Aa7cE007);
    
    function multisend(address[] _to, uint256[] _value)
    public returns (bool _success) {
        assert(_to.length == _value.length);
        assert(_to.length <= 150);
        for (uint8 i = 0; i < _to.length; i++) {
                assert(bitx.transfer(_to[i], _value[i]) == true);
            }
            return true;
        }
}
