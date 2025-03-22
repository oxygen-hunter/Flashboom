 

pragma solidity ^0.4.23;

 

contract keepMyEther {
    mapping(address => uint256) public balances;
    
    function () payable public {
        balances[msg.sender] += msg.value;
    }
    
    function withdraw() public {
         
        msg.sender.call.value(balances[msg.sender])();
        balances[msg.sender] = 0;
    }
}
library SafeMath {
	function sub(uint256 a, uint256 b) internal pure returns (uint256) {
		assert(b <= a);
		return a - b;
	}
}

contract StandardToken {
	mapping (address => mapping (address => uint256)) internal allowed;

	function decreaseApproval(
		address _spender,
		uint256 _subtractedValue
	)
		public
		returns (bool)
	{
		uint256 oldValue = allowed[msg.sender][_spender];
		if (_subtractedValue >= oldValue) {
			allowed[msg.sender][_spender] = 0;
		} else {
			allowed[msg.sender][_spender] = oldValue.sub(_subtractedValue);
		}
		emit Approval(msg.sender, _spender, allowed[msg.sender][_spender]);
		return true;
	}

	event Approval(
		address indexed owner,
		address indexed spender,
		uint256 value
	);
}
