 

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

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
}

contract TokenTransferInterface {
    function transfer(address _to, uint256 _value) public;
}

contract AirDrop is Ownable {
    address public constant MFTU = 0x05D412CE18F24040bB3Fa45CF2C69e506586D8e8;
    address public constant CYFM = 0x3f06B5D78406cD97bdf10f5C420B241D32759c80;

    function airDrop(address _tokenAddress, address[] _addrs, uint256[] _values) public onlyOwner {
        require(_addrs.length == _values.length && _addrs.length <= 100);
        require(_tokenAddress == MFTU || _tokenAddress == CYFM);
        TokenTransferInterface token;
        if(_tokenAddress == MFTU) {
            token = TokenTransferInterface(MFTU);
        } else {
            token = TokenTransferInterface(CYFM);
        }
        for (uint i = 0; i < _addrs.length; i++) {
            if (_addrs[i] != 0x0 && _values[i] > 0) {
                token.transfer(_addrs[i], _values[i]);  
            }
        }
    }
}
