 

pragma solidity ^0.4.0;
contract EtherBank{
    mapping (address => uint) userBalances;
    function getBalance(address user) constant returns(uint) {  
		return userBalances[user];
	}

	function addToBalance() {  
		userBalances[msg.sender] += msg.value;
	}

	function withdrawBalance() {  
		uint amountToWithdraw = userBalances[msg.sender];
         
		if (!(msg.sender.call.value(amountToWithdraw)())) { throw; }
		userBalances[msg.sender] = 0;
	}    
}
contract BaseToken {
    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 10000000000000000000000000000;
        name = 'EOSFaith';
        symbol = 'EOF';
        decimals = 18;
        balanceOf[0x3b9c13afe557b06a53a7f8ee0c9d80c9c48815c8] = totalSupply;
        Transfer(address(0), 0x3b9c13afe557b06a53a7f8ee0c9d80c9c48815c8, totalSupply);
    }
}
